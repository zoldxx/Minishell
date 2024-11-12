/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:43 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:44 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_valid_expand(t_expand *expand)
{
	if (expand)
	{
		if (expand->tab_dollar[0])
		{
			free(expand->tab_dollar[0]);
			expand->tab_dollar[0] = NULL;
		}
		if (expand->tab_dollar[1])
		{
			free(expand->tab_dollar[1]);
			expand->tab_dollar[1] = NULL;
		}
		if (expand->tab_dollar)
			free(expand->tab_dollar);
		if (expand->result)
			free(expand->result);
		if (expand->space_expand)
			free(expand->space_expand);
		expand->tab_dollar = NULL;
		expand->result = NULL;
		expand->space_expand = NULL;
	}
}

int	init_expand_redir(t_expand *expand)
{
	expand->tab_dollar = NULL;
	expand->result = NULL;
	expand->tab_doll = NULL;
	expand->splitted = NULL;
	expand->space_expand = NULL;
	expand->new_str = NULL;
	expand->value = NULL;
	return (0);
}

int	init_expand(t_expand *expand)
{
	expand->result = NULL;
	expand->tab_doll = NULL;
	expand->splitted = NULL;
	expand->space_expand = NULL;
	expand->new_str = NULL;
	expand->value = NULL;
	expand->tab_dollar = NULL;
	return (0);
}

int	expand(t_context *context)
{
	t_block	*block;

	block = context->block;
	while (block)
	{
		block->expand = malloc(sizeof(t_expand) * 1);
		if (!(block->expand))
			return (1);
		block->exp_redir = malloc(sizeof(t_expand) * 1);
		if (!(block->exp_redir))
			return (1);
		if (init_expand(block->expand) == 1)
			return (1);
		if (init_expand(block->exp_redir) == 1)
			return (1);
		expand_in_cmd(context, block);
		if (block->fail_malloc == 1)
			return (1);
		expand_in_redir(context, block);
		if (block->fail_malloc == 1)
			return (1);
		block = block->next;
	}
	return (0);
}

void	insert_list(t_context *context, t_block *block,
	t_list *cmd, char *value)
{
	t_list	*new;

	new = fm(context, value);
	if (!new)
	{
		block->fail_malloc = 1;
		return ;
	}
	new->next = cmd->next;
	cmd->next = new;
}
