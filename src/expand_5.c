/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:45 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:46 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_or_not(t_block *block, int nb_dollar, int **i)
{
	if (block->expand->tab_dollar[0][nb_dollar] == 0)
	{
		while (++((*i)[1]) < block->expand->tab_dollar[1][nb_dollar])
			(*i)[0]++;
	}
	else if (block->expand->tab_dollar[0][nb_dollar] == 1)
	{
		while (++((*i)[1]) < block->expand->tab_dollar[1][nb_dollar])
		{
			block->expand->result[(*i)[2]] = block->expand
				->new_str[(*i)[0] - 1];
			(*i)[0]++;
			(*i)[2]++;
		}
		block->expand->result[(*i)[2]] = block->expand->new_str[(*i)[0] - 1];
		(*i)[2]++;
	}	
	else
		expand_or_not_suite(block, nb_dollar, i);
}

char	*enleve_dollar(t_context *context, t_block *block, int taille)
{
	int		*i;
	int		nb_dollar;

	(void)context;
	nb_dollar = 0;
	if (!init_enleve_dollar(block, &block->expand->result, &i, taille))
		return (NULL);
	while (block->expand->new_str[i[0]])
	{
		if (block->expand->new_str[i[0]] == '$')
		{
			i[1] = -1;
			i[0]++;
			expand_or_not(block, nb_dollar, &i);
			if (block->fail_malloc == 1)
				return (NULL);
			nb_dollar++;
		}
		else
			block->expand->result[i[2]++] = block->expand->new_str[i[0]++];
	}
	return (block->expand->result[i[2]] = '\0', free(i), block->expand->result);
}

void	expredir_or_not_end(t_block *block, int nb_dollar, int **i)
{
	if (block->exp_redir->tab_dollar[0][nb_dollar] == 3)
	{
		block->exp_redir->value = ft_itoa(block->context->exit_code);
		if (!(block->exp_redir->value))
		{
			block->fail_malloc = 1;
			return ;
		}
		ft_strlcpy(block->exp_redir->result + (*i)[2], block->exp_redir->value,
			ft_strlen(block->exp_redir->value) + 1);
		(*i)[2] += ft_strlen(block->exp_redir->value);
		free(block->exp_redir->value);
		block->exp_redir->value = NULL;
		(*i)[0]++;
	}
}

void	expredir_or_not_suite(t_block *block,
	int nb_dollar, int **i)
{
	if (block->exp_redir->tab_dollar[0][nb_dollar] == 2)
	{
		while (++((*i)[1]) < block->exp_redir->tab_dollar[1][nb_dollar])
			(*i)[0]++;
		block->exp_redir->value = get_value(block->context,
				block->exp_redir->new_str + (*i)[0]
				- block->exp_redir->tab_dollar[1][nb_dollar],
				block->exp_redir->tab_dollar[1][nb_dollar]);
		ft_strlcpy(block->exp_redir->result + (*i)[2], block->exp_redir->value,
			ft_strlen(block->exp_redir->value) + 1);
		(*i)[2] += ft_strlen(block->exp_redir->value);
	}
	else
		expredir_or_not_end(block, nb_dollar, i);
}

void	expredir_or_not(t_block *block, int nb_dollar, int **i)
{
	if (block->exp_redir->tab_dollar[0][nb_dollar] == 0)
	{
		while (++((*i)[1]) < block->exp_redir->tab_dollar[1][nb_dollar])
			(*i)[0]++;
	}
	else if (block->exp_redir->tab_dollar[0][nb_dollar] == 1)
	{
		while (++((*i)[1]) < block->exp_redir->tab_dollar[1][nb_dollar])
		{
			block->exp_redir->result[(*i)[2]] = block->exp_redir
				->new_str[(*i)[0] - 1];
			(*i)[0]++;
			(*i)[2]++;
		}
		block->exp_redir->result[(*i)[2]] = block->exp_redir
			->new_str[(*i)[0] - 1];
		(*i)[2]++;
	}	
	else
		expredir_or_not_suite(block, nb_dollar, i);
}
