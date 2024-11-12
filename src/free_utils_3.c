/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:17 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:56:27 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_elist(t_elist *list)
{
	t_elist	*temp;

	temp = NULL;
	if (list)
	{
		while (list)
		{
			temp = list->next;
			free(list);
			list = temp;
		}
		free(list);
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab && tab[++i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		if (tab[i])
			free(tab[i]);
		tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
}

void	ft_free_expand_cmd(t_block *block)
{
	t_expand	*tmp;

	tmp = block->expand;
	if (tmp && tmp->result)
		free(tmp->result);
	if (tmp && tmp->tab_dollar)
	{
		if (tmp && tmp->tab_dollar[0])
			free(tmp->tab_dollar[0]);
		if (tmp && tmp->tab_dollar[1])
			free(tmp->tab_dollar[1]);
		free(tmp->tab_dollar);
	}
	if (tmp && tmp->splitted)
		ft_free_tab(tmp->splitted);
	if (tmp && tmp->space_expand)
		free(tmp->space_expand);
	if (tmp && tmp->new_str)
		free(tmp->new_str);
	if (tmp && tmp->tab_doll)
		free(tmp->tab_doll);
	if (tmp && tmp->value)
		free(tmp->value);
}

void	ft_free_expand_redir(t_block *block)
{
	t_expand	*tmp;

	tmp = block->exp_redir;
	if (tmp && tmp->result)
		free(tmp->result);
	if (tmp && tmp->tab_dollar)
	{
		if (tmp && tmp->tab_dollar[0])
			free(tmp->tab_dollar[0]);
		if (tmp && tmp->tab_dollar[1])
			free(tmp->tab_dollar[1]);
		free(tmp->tab_dollar);
	}
	if (tmp && tmp->splitted)
		ft_free_tab(tmp->splitted);
	if (tmp && tmp->space_expand)
		free(tmp->space_expand);
	if (tmp && tmp->new_str)
		free(tmp->new_str);
	if (tmp && tmp->tab_doll)
		free(tmp->tab_doll);
	if (tmp && tmp->value)
		free(tmp->value);
}

void	ft_free_fail_expand(t_context *context)
{
	t_block	*block;

	block = context->block;
	ft_putstr_fd("MALLOC FAIL\n", 2);
	while (block)
	{
		ft_free_expand_cmd(block);
		ft_free_expand_redir(block);
		block = block->next;
	}
	exit (1);
}
