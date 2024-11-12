/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:50 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:51 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	v(t_context *context, char *str, int i, int j)
{
	if (str[i] == '?')
		return (3);
	else if (value_existe(context, str, i, j) == 1)
		return (2);
	else if (value_existe(context, str, i, j) == 2)
		return (0);
	else
		return (0);
}

int	util_is_expendable(t_block *block, int **td, int *nb_dollar)
{
	*td = malloc(sizeof(int) * (*(nb_dollar)));
	if (!(*td))
	{
		block->fail_malloc = 1;
		return (0);
	}
	*nb_dollar = 0;
	return (1);
}

int	init_exp(int *i, int *j, int *quote)
{
	*i = 0;
	*j = 0;
	*quote = 0;
	return (1);
}

int	*is_expendable(t_context *context, t_block *block, char *str, int nb_dollar)
{
	int	i;
	int	j;
	int	quote;
	int	*td;

	td = NULL;
	if (init_exp(&i, &j, &quote) && !util_is_expendable(block, &td, &nb_dollar))
		return (NULL);
	while (str[i])
	{
		quote = is_quoted(str[i], 0);
		if (str[i] == '$')
		{
			j = ++i;
			is_interr(str, &i);
			if (quote == 1)
				td[nb_dollar] = 1;
			else
				td[nb_dollar] = v(context, str, i, j);
			nb_dollar++;
		}
		else
			i++;
	}
	return (is_quoted('a', 1), td);
}

int	calcul_len(t_context *context, int *tab_dollar, char *str)
{
	int	len_final;
	int	i;
	int	j;
	int	nb_dollar;

	init_exp(&i, &j, &nb_dollar);
	len_final = ft_strlen(str) - nb_quotes(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = ++i;
			is_interr(str, &i);
			if (tab_dollar[nb_dollar] == 0)
				len_final -= i - j + 1;
			else if (tab_dollar[nb_dollar] == 2)
				len_final += value_size(context, str, i, j) - (i - j + 1);
			else if (tab_dollar[nb_dollar] == 3)
				len_final += nb_char_interr(context) - 2;
			nb_dollar++;
		}
		else
			i++;
	}
	return (len_final);
}
