/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:10 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:11 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_env(t_context *context, char *new_kv)
{
	t_elist	*temp;
	int		i;

	i = 0;
	temp = context->env;
	while (temp)
	{
		while (temp->content[0][i] && new_kv[i] && new_kv[i] != '=')
		{
			if (temp->content[0][i] == new_kv[i])
				i++;
			else
				break ;
		}
		if (new_kv[i] == '=' && temp->content[0][i] == '\0')
			return (1);
		temp = temp->next;
		i = 0;
	}
	return (0);
}

int	is_in_hide_env(t_context *context, char *new_kv)
{
	t_elist	*temp;
	int		i;

	i = 0;
	temp = context->hide_env;
	while (temp)
	{
		while (temp->content[0][i] && new_kv[i] && new_kv[i] != '=')
		{
			if (temp->content[0][i] == new_kv[i])
				i++;
			else
				break ;
		}
		if ((new_kv[i] == '\0' || new_kv[i] == '=')
			&& temp->content[0][i] == '\0')
			return (1);
		temp = temp->next;
		i = 0;
	}
	return (0);
}

int	contain_an_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
