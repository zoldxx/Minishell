/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:42 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:43 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	boucle_split_expand(t_expand *expand, int *i, int *nb_spaces,
		int max_spaces)
{
	while (expand->result[*i] && expand->result[*i] == ' '
		&& *nb_spaces < max_spaces && expand->space_expand[*nb_spaces] == 1)
	{
		(*nb_spaces)++;
		(*i)++;
	}
}

void	middle_split_expand(t_expand *expand, int *i, int *nb_spaces,
		int max_spaces)
{
	while (expand->result && expand->result[*i] && *nb_spaces < max_spaces
		&& expand->space_expand[*nb_spaces] != 1)
	{
		if (expand->result[*i] && expand->result[*i] == ' '
			&& expand->space_expand[*nb_spaces] == 0)
			(*nb_spaces)++;
		(*i)++;
	}
}

void	split_expand(t_block *block, int tot_spaces, int max_spaces)
{
	int			i;
	int			j;
	int			word;
	int			nb_spaces;
	t_expand	*expand;

	expand = block->expand;
	if (init_exp(&i, &nb_spaces, &word) && !ise(block, expand, tot_spaces))
		return ;
	while (expand->result[i])
	{
		boucle_split_expand(expand, &i, &nb_spaces, max_spaces);
		j = i;
		middle_split_expand(expand, &i, &nb_spaces, max_spaces);
		while (expand->result[i] && expand->result[i] != ' ')
			i++;
		expand->splitted[word] = create_word(block, expand->result, i, j);
		if (block->fail_malloc == 1)
			return ;
		word++;
		boucle_split_expand(expand, &i, &nb_spaces, max_spaces);
	}
	expand->splitted[word] = NULL;
	return ;
}

void	split_expand_redir(t_block *block, int tot_spaces, int max_spaces)
{
	int			i;
	int			j;
	int			word;
	int			nb_spaces;
	t_expand	*expand;

	expand = block->exp_redir;
	if (init_exp(&i, &nb_spaces, &word) && !ise_r(block, expand, tot_spaces))
		return ;
	while (expand->result[i])
	{
		boucle_split_expand(expand, &i, &nb_spaces, max_spaces);
		j = i;
		middle_split_expand(expand, &i, &nb_spaces, max_spaces);
		while (expand->result[i] && expand->result[i] != ' ')
			i++;
		expand->splitted[word] = create_word(block, expand->result, i, j);
		if (block->fail_malloc == 1)
			return ;
		word++;
		boucle_split_expand(expand, &i, &nb_spaces, max_spaces);
	}
	expand->splitted[word] = NULL;
	return ;
}

// void	split_expand_redir(t_block *block, int *space_expand, int tot_spaces,
// 		int max_spaces)
// {
// 	int			i;
// 	int			j;
// 	int			word;
// 	int			nb_spaces;
// 	t_expand	*expand_redir;

// 	expand_redir = block->exp_redir;
// 	i = 0;
// 	nb_spaces = 0;
// 	word = 0;
// 	if (!(expand_redir->result[i]))
// 	{
// 		expand_redir->splitted = NULL;
// 		return ;
// 	}
// 	expand_redir->splitted = malloc(sizeof(char *) * (tot_spaces + 1));
// 	if (!expand_redir->splitted)
// 	{
// 		block->fail_malloc = 1;
// 		return ;
// 	}
// 	while (expand_redir->result[i])
// 	{
// 		while (expand_redir->result[i] && expand_redir->result[i] == ' '
// 			&& nb_spaces < max_spaces && space_expand[nb_spaces] == 1)
// 		{
// 			nb_spaces++;
// 			i++;
// 		}
// 		j = i;
// 		while (expand_redir->result[i] && nb_spaces < max_spaces
// 			&& space_expand[nb_spaces] != 1)
// 		{
// 			if (expand_redir->result[i] && expand_redir->result[i] == ' '
// 				&& space_expand[nb_spaces] == 0)
// 				nb_spaces++;
// 			i++;
// 		}
// 		while (expand_redir->result[i] && expand_redir->result[i] != ' ')
// 			i++;
// 		expand_redir->splitted[word] = create_word(block, expand_redir->result,
// 				i, j);
// 		if (block->fail_malloc == 1)
// 			return ;
// 		word++;
// 		while (expand_redir->result[i] && expand_redir->result[i] == ' '
// 			&& nb_spaces < max_spaces && space_expand[nb_spaces] == 1)
// 		{
// 			nb_spaces++;
// 			i++;
// 		}
// 	}
// 	expand_redir->splitted[word] = NULL;
// 	return ;
// }

// void	split_expand(t_block *block, int *space_expand, int tot_spaces,
// 		int max_spaces)
// {
// 	int			i;
// 	int			j;
// 	int			word;
// 	int			nb_spaces;
// 	t_expand	*expand;

// 	expand = block->expand;
// 	i = 0;
// 	nb_spaces = 0;
// 	word = 0;
// 	if (!(expand->result[i]))
// 	{
// 		expand->splitted = NULL;
// 		return ;
// 	}
// 	expand->splitted = malloc(sizeof(char *) * (tot_spaces + 1));
// 	if (!expand->splitted)
// 	{
// 		block->fail_malloc = 1;
// 		return ;
// 	}
// 	while (expand->result[i])
// 	{
// 		while (expand->result[i] && expand->result[i] == ' '
// 			&& nb_spaces < max_spaces && space_expand[nb_spaces] == 1)
// 		{
// 			nb_spaces++;
// 			i++;
// 		}
// 		j = i;
// 		while (expand->result[i] && nb_spaces < max_spaces
// 			&& space_expand[nb_spaces] != 1)
// 		{
// 			if (expand->result[i] && expand->result[i] == ' '
// 				&& space_expand[nb_spaces] == 0)
// 				nb_spaces++;
// 			i++;
// 		}
// 		while (expand->result[i] && expand->result[i] != ' ')
// 			i++;
// 		expand->splitted[word] = create_word(block, expand->result, i, j);
// 		if (block->fail_malloc == 1)
// 			return ;
// 		word++;
// 		while (expand->result[i] && expand->result[i] == ' '
// 			&& nb_spaces < max_spaces && space_expand[nb_spaces] == 1)
// 		{
// 			nb_spaces++;
// 			i++;
// 		}
// 	}
// 	expand->splitted[word] = NULL;
// 	return ;
// }

// int	*fill_space_expand(t_context *context, t_block *block, char *str,
// 		int **tab_dollar)
// {
// 	int		i;
// 	int		j;
// 	int		nb_dollar;
// 	int		nb_spaces;
// 	int		*space_expand;
// 	char	*value;

// 	i = 0;
// 	nb_dollar = 0;
// 	nb_spaces = 0;
// 	space_expand = malloc(sizeof(int) * nb_space(context, str, tab_dollar));
// 	if (!(space_expand))
// 	{
// 		block->fail_malloc = 1;
// 		return (NULL);
// 	}
// 	while (str[i])
// 	{
// 		if (str[i] == ' ')
// 		{
// 			space_expand[nb_spaces] = 0;
// 			nb_spaces++;
// 		}
// 		else if (str[i] == '$' && tab_dollar[0][nb_dollar] == 2)
// 		{
// 			value = get_value(context, str + i + 1, tab_dollar[1][nb_dollar]);
// 			j = -1;
// 			while (++j < little_nb_space(value))
// 			{
// 				space_expand[nb_spaces] = 1;
// 				nb_spaces++;
// 			}
// 			nb_dollar++;
// 		}
// 		else if (str[i] == '$' && tab_dollar[0][nb_dollar] != 2)
// 			nb_dollar++;
// 		i++;
// 	}
// 	return (space_expand);
// }

// char	**split_expand(char *str, int *space_expand,
// int tot_spaces,int max_spaces)
// {
// 	char	**result;
// 	int		i;
// 	int		j;
// 	int		word;
// 	int		nb_spaces;

// 	i = 0;
// 	nb_spaces = 0;
// 	word = 0;
// 	// if (!str[i])
// 	// {
// 	// 	result = malloc(sizeof(char *) * 2);
// 	// 	if (!result)
// 	// 		return (NULL);
// 	// 	result[0] = malloc(sizeof(char) * 1);
// 	// 	if (!result[0])
// 	// 		return (NULL);
// 	// 	result[0][0] = '\0';
// 	// 	result[1] = NULL;
// 	// 	return (result);
// 	// }
// 	result = malloc(sizeof(char *) * (tot_spaces + 1));
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] == ' ' && nb_spaces < max_spaces
//&& space_expand[nb_spaces] == 1)
// 		{
// 			nb_spaces++;
// 			i++;
// 		}
// 		j = i;
// 		while (str[i] && nb_spaces < max_spaces && space_expand[nb_spaces] != 1)
// 		{
// 			if (str[i] && str[i] == ' ' && space_expand[nb_spaces] == 0)
// 				nb_spaces++;
// 			i++;
// 		}
// 		while (str[i] && str[i] != ' ')
// 			i++;
// 		result[word] = create_word(str, i, j);
// 		word++;
// 		while (str[i] && str[i] == ' ' && nb_spaces < max_spaces
//		&& space_expand[nb_spaces] == 1)
// 		{
// 			nb_spaces++;
// 			i++;
// 		}
// 	}
// 	result[word] = NULL;
// 	return (result);
// }
