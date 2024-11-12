/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_9.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:55 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:56 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	util_size_key(t_block *block, int nb_dollar)
{
	block->expand->tab_dollar[1] = malloc(sizeof(int) * nb_dollar);
	if (!block->expand->tab_dollar[1])
	{
		block->fail_malloc = 1;
		return (0);
	}
	return (1);
}

int	is_separator(char c)
{
	if (c != '$' && c != ' ' && c != '\t' && c != '\'' && c != '\"')
		return (0);
	return (1);
}

char	*enleve_quotes_redir(t_block *block, char *str)
{
	int		i;
	int		j;
	int		quote;

	if (init_exp(&i, &j, &quote) && !util_eq(block,
			&block->exp_redir->new_str, str))
		return (NULL);
	while (str[i])
	{
		while (str[i] && quote == 0)
		{
			quote = is_quoted(str[i], 0);
			if (str[i] && quote == 0)
				block->exp_redir->new_str[j++] = str[i];
			i++;
		}
		while (str[i] && quote != 0)
		{
			quote = is_quoted(str[i], 0);
			if (str[i] && quote != 0)
				block->exp_redir->new_str[j++] = str[i];
			i++;
		}
	}
	return (block->exp_redir->new_str[j] = '\0', is_quoted('a', 1), "");
}
