/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:40 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:41 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_nbstring_expand(char const *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (s[0] == ' ')
		res = 1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			res += 1;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (res);
}

int	little_nb_space(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			nb++;
		i++;
	}
	return (nb);
}

int	nb_space(t_context *context, char *str, int **tab_dollar)
{
	int		i;
	int		nb;
	int		nb_dollar;
	char	*value;

	i = 0;
	nb = 0;
	nb_dollar = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			nb++;
		else if (str[i] == '$' && tab_dollar[0][nb_dollar] == 2)
		{
			value = get_value(context, str + i + 1, tab_dollar[1][nb_dollar]);
			nb += little_nb_space(value);
			nb_dollar++;
		}
		else if (str[i] == '$' && tab_dollar[0][nb_dollar] != 2)
			nb_dollar++;
		i++;
	}
	return (nb);
}

int	nb_space_split(t_context *context, char *str, int **tab_dollar)
{
	int		i;
	int		nb;
	int		nb_dollar;
	char	*value;

	i = 0;
	nb = 1;
	nb_dollar = 0;
	while (str[i])
	{
		if (str[i] == '$' && tab_dollar[0][nb_dollar] == 2)
		{
			value = get_value(context, str + i + 1, tab_dollar[1][nb_dollar]);
			nb += ft_nbstring_expand(value, ' ') - 1;
			nb_dollar++;
		}
		else if (str[i] == '$' && tab_dollar[0][nb_dollar] != 2)
			nb_dollar++;
		i++;
	}
	return (nb);
}

int	init_fse(t_block *block, char *str, int **tab_dollar)
{
	block->expand->space_expand = ft_calloc(nb_space(block->context,
				str, tab_dollar), sizeof(int));
	if (!(block->expand->space_expand))
	{
		block->fail_malloc = 1;
		return (0);
	}
	return (1);
}
