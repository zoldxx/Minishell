/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:57 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:58 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*insert_first_cmd(t_list *cmd, t_block *block, int *i, int *j)
{
	t_expand	*expand;

	expand = block->expand;
	if (cmd->content)
		free(cmd->content);
	cmd->content = expand->splitted[0];
	if (expand->splitted[0])
	{	
		while (expand->splitted[(*i)])
			(*i)++;
		(*i)--;
		(*j) = (*i);
		while ((*i) > 0)
		{
			insert_list(block->context, block, cmd, expand->splitted[(*i)]);
			(*i)--;
		}
		while ((*j) > 0)
		{
			cmd = cmd->next;
			(*j)--;
		}
	}
	return (cmd);
}

void	boucle_expand_cmd(t_block *block, t_context *context, int *i, int *j)
{
	t_list	*temp;

	temp = NULL;
	while (block->cmd_expand && block->cmd_expand->next)
	{
		*i = 1;
		temp = block->cmd_expand->next->next;
		expand_total(context, block, block->cmd_expand->next->content);
		if (block->fail_malloc == 1)
			return ;
		free(block->cmd_expand->next->content);
		if (!block->expand->splitted)
		{
			free(block->cmd_expand->next);
			block->cmd_expand->next = temp;
		}
		else
		{
			insert_command(block, block->expand->splitted, i, j);
			if (block->fail_malloc == 1)
				return ;
		}
	}
}

void	free_in_insert(t_list *cmd)
{
	if (cmd)
	{
		if (cmd->content)
			free(cmd->content);
		free(cmd);
	}
}

void	expand_in_cmd_utils(t_block *block, t_context *context)
{
	t_list	*temp;

	temp = NULL;
	while (!(block->expand->splitted) && block->cmd_expand)
	{
		temp = block->cmd_expand->next;
		free_in_insert(block->cmd_expand);
		block->cmd_expand = temp;
		block->cmd_list = block->cmd_expand;
		if (block->cmd_expand)
		{
			expand_total(context, block, block->cmd_expand->content);
			if (block->fail_malloc == 1)
				return ;
		}
	}
}

void	expand_in_cmd(t_context *context, t_block *block)
{
	int		i[2];

	i[1] = 1;
	block->cmd_expand = block->cmd_list;
	if (block->cmd_expand)
	{
		expand_total(context, block, block->cmd_expand->content);
		if (block->fail_malloc == 1)
			return ;
		expand_in_cmd_utils(block, context);
		i[0] = 1;
		if (block->cmd_expand)
			block->cmd_expand = insert_first_cmd(block->cmd_expand, block,
					&(i[0]), &(i[1]));
		if (block->expand->splitted)
		{
			free(block->expand->splitted);
			block->expand->splitted = NULL;
		}
		boucle_expand_cmd(block, context, &(i[0]), &(i[1]));
		if (block->fail_malloc == 1)
			return ;
	}
}

// void	expand_in_cmd(t_context *context, t_block *block)
// {
// 	t_list	*temp;
// 	int		i[2];

// 	i[1] = 1;
// 	block->cmd_expand = block->cmd_list;
// 	if (block->cmd_expand)
// 	{
// 		expand_total(context, block, block->cmd_expand->content);
// 		if (block->fail_malloc == 1)
// 			return ;
// 		while (!(block->expand->splitted) && block->cmd_expand)
// 		{
// 			temp = block->cmd_expand->next;
// 			free_in_insert(block->cmd_expand);
// 			block->cmd_expand = temp;
// 			block->cmd_list = block->cmd_expand;
// 			if (block->cmd_expand)
// 			{
// 				expand_total(context, block, block->cmd_expand->content);
// 				if (block->fail_malloc == 1)
// 					return ;
// 			}
// 		}
// 		i[0] = 1;
// 		if (block->cmd_expand)
// 			block->cmd_expand = insert_first_cmd(block->cmd_expand, block,
//		&(i[0]), &(i[1]));
// 		free(block->expand->splitted);
// 		block->expand->splitted = NULL;
// 		boucle_expand_cmd(block, context, &(i[0]), &(i[1]));
// 		if (block->fail_malloc == 1)
// 			return ;
// 	}
// }
