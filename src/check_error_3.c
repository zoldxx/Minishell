/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:25 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:26 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_2_different_chevrons(char *str, int i)
{
	while (str[i])
	{
		while (str[i] && is_quoted(str[i], 0))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i] && !is_quoted(str[i], 0) && str[i] == '<')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '>' || str[i] == '|')
				return (is_quoted('a', 1),
					printf("syntax error near unexpected token `%c'\n",
						str[i]));
			else if (str[i])
			{
				is_quoted(str[i], 0);
				i++;
			}
		}
		else if (str[i])
			i++;
	}
	return (is_quoted('a', 1), 0);
}

int	is_2_different_chevrons_bis(char *str, int i)
{
	while (str[i])
	{
		while (str[i] && is_quoted(str[i], 0))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i] && !is_quoted(str[i], 0) && str[i] == '>')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '<' || str[i] == '|')
				return (is_quoted('a', 1),
					printf("syntax error near unexpected token `%c'\n",
						str[i]));
			else if (str[i])
			{
				is_quoted(str[i], 0);
				i++;
			}
		}
		else if (str[i])
			i++;
	}
	return (is_quoted('a', 1), 0);
}

void	utils_quoted(char c, int *i)
{
	is_quoted(c, 0);
	*i += 1;
}

int	is_spaces_between_left_chevrons(char *str, int i)
{
	while (str[i])
	{
		while (str[i] && is_quoted(str[i], 0))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i] && !is_quoted(str[i], 0) && str[i] == '<')
		{
			i++;
			if (str[i] == ' ' || str[i] == '\t')
			{
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				if (str[i] == '<' || str[i] == '|')
					return (is_quoted('a', 1),
						printf("syntax error near unexpected token `%c'\n",
							str[i]));
			}
			else if (str[i])
				utils_quoted(str[i], &i);
		}
		else if (str[i])
			i++;
	}
	return (is_quoted('a', 1), 0);
}

int	is_spaces_between_right_chevrons(char *str, int i)
{
	while (str[i])
	{
		while (str[i] && is_quoted(str[i], 0))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i] && !is_quoted(str[i], 0) && str[i] == '>')
		{
			i++;
			if (str[i] == ' ' || str[i] == '\t')
			{
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				if (str[i] == '>' || str[i] == '|')
					return (is_quoted('a', 1),
						printf("syntax error near unexpected token `%c'\n",
							str[i]));
			}
			else if (str[i])
				utils_quoted(str[i], &i);
		}
		else if (str[i])
			i++;
	}
	return (is_quoted('a', 1), 0);
}
