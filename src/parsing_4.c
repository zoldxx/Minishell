/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:14 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:15 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	move_forward_in_block_line(t_context *context, t_block *block,
// 	int *i, int *j)
// {
// 	while (context->is_created == 1 && block->block_line[*i]
// 		&& (block->block_line[*i] == ' ' || block->block_line[*i] == '\t'))
// 	{
// 		(*i) += 1;
// 		(*j) = (*i);
// 	}
// 	context->is_created = 0;
// 	while (block->block_line[*i] && is_quoted(block->block_line[*i], 0))
// 		(*i) += 1;
// 	if (block->block_line[*i] == '\'' || block->block_line[*i] == '\"')
// 		(*i) += 1;
// }

// int	move_forward_in_block_line(t_context *context, t_block *block,
// 	int *i, int *j)
// {
// 	while (context->is_created == 1 && block->block_line[*i]
// 		&& (block->block_line[*i] == ' ' || block->block_line[*i] == '\t'))
// 	{
// 		(*i) += 1;
// 		(*j) = (*i);
// 	}
// 	context->is_created = 0;
// 	while (block->block_line[*i] && is_quoted(block->block_line[*i], 0))
// 		(*i) += 1;
// 	if (block->block_line[*i] == '\'' || block->block_line[*i] == '\"')
// 		(*i) += 1;
// 	return (1);
// }

int	mf(t_context *context, t_block *block, int *i, int *j)
{
	while (context->is_created == 1 && block->block_line[*i]
		&& (block->block_line[*i] == ' ' || block->block_line[*i] == '\t'))
	{
		(*i) += 1;
		(*j) = (*i);
	}
	context->is_created = 0;
	while (block->block_line[*i] && is_quoted(block->block_line[*i], 0))
		(*i) += 1;
	if (block->block_line[*i] == '\'' || block->block_line[*i] == '\"')
		(*i) += 1;
	return (1);
}

int	ced(t_context *context)
{
	if (!check_error(context->input_line))
	{
		context->exit_code = 2;
		return (0);
	}
	return (1);
}

int	end_d(t_context *context)
{
	if (separe_args_redir(context) == 1)
	{
		ft_free_loop(context);
		return (0);
	}
	return (1);
}
