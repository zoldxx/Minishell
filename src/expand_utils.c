/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:06 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:07 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	splitted_exist(char **splitted)
{
	free(splitted);
	splitted = NULL;
}

void	insert_command(t_block *block, char **splitted, int *i, int *j)
{
	if (splitted && splitted[0])
	{
		block->cmd_expand->next->content = splitted[0];
		while (splitted[(*i)])
			(*i)++;
		(*i)--;
		(*j) = (*i);
		while ((*i) > 0)
		{
			insert_list(block->context, block,
				block->cmd_expand->next, splitted[(*i)]);
			if (block->fail_malloc == 1)
				return ;
			(*i)--;
		}
		while ((*j) > 0)
		{
			block->cmd_expand = block->cmd_expand->next;
			(*j)--;
		}
	}
	if (splitted)
		splitted_exist(splitted);
	block->cmd_expand = block->cmd_expand->next;
}

t_redir	*insert_redir(t_redir *redir, t_block *block, int *i, int *j)
{
	if (block->exp_redir->splitted && block->exp_redir->splitted[0])
	{
		redir->next->filename = block->exp_redir->splitted[0];
		while (block->exp_redir->splitted[(*i)])
			(*i)++;
		(*i)--;
		(*j) = (*i);
		while ((*i) > 0)
		{
			insert_redir_list(block, redir->next,
				block->exp_redir->splitted[(*i)]);
			if (block->fail_malloc == 1)
				return (NULL);
			(*i)--;
		}
		while ((*j) > 0)
		{
			redir = redir->next;
			(*j)--;
		}
	}
	if (block->exp_redir->splitted)
		splitted_exist(block->exp_redir->splitted);
	redir = redir->next;
	return (redir);
}

// void	insert_command(t_block *block, char **splitted, int *i, int *j)
// {
// 	if (splitted && splitted[0])
// 	{
// 		block->cmd_expand->next->content = splitted[0];
// 		while (splitted[(*i)])
// 			(*i)++;
// 		(*i)--;
// 		(*j) = (*i);
// 		while ((*i) > 0)
// 		{
// 			insert_list(block, block->cmd_expand->next, splitted[(*i)]);
// 			if (block->fail_malloc == 1)
// 				return ;
// 			(*i)--;
// 		}
// 		while ((*j) > 0)
// 		{
// 			block->cmd_expand = block->cmd_expand->next;
// 			(*j)--;
// 		}
// 	}
// 	if (splitted)
// 	{
// 		free(splitted);
// 		splitted = NULL;
// 	}
// 	block->cmd_expand = block->cmd_expand->next;
// }

// t_redir	*insert_redir(t_redir *redir, t_block *block, int *i, int *j)
// {
// 	if (block->exp_redir->splitted && block->exp_redir->splitted[0])
// 	{
// 		redir->next->filename = block->exp_redir->splitted[0];
// 		while (block->exp_redir->splitted[(*i)])
// 			(*i)++;
// 		(*i)--;
// 		(*j) = (*i);
// 		while ((*i) > 0)
// 		{
// 			insert_redir_list(block, redir->next,
// 				block->exp_redir->splitted[(*i)]);
// 			if (block->fail_malloc == 1)
// 				return (NULL);
// 			(*i)--;
// 		}
// 		while ((*j) > 0)
// 		{
// 			redir = redir->next;
// 			(*j)--;
// 		}
// 	}
// 	if (block->exp_redir->splitted)
// 	{
// 		free(block->exp_redir->splitted);
// 		block->exp_redir->splitted = NULL;
// 	}
// 	redir = redir->next;
// 	return (redir);
// }
