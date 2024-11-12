/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:57 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:58 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mult_redir_one(t_context *context, t_block *block)
{
	if (block->fd_input != 0)
		dup2(block->fd_input, STDIN_FILENO);
	if (block->fd_output != 1)
		dup2(block->fd_output, STDOUT_FILENO);
	else
		dup2(context->pipe_cmd[1], STDOUT_FILENO);
	ft_close_multiple(context->pipe_cmd[0], context->pipe_cmd[1],
		block->fd_input, block->fd_output);
}

void	mult_redir_two(t_context *context, t_block *block)
{
	if (block->fd_input != 0)
		dup2(block->fd_input, STDIN_FILENO);
	else
		dup2(context->fd_temp, STDIN_FILENO);
	if (block->fd_output != 1)
		dup2(block->fd_output, STDOUT_FILENO);
	if (context->fd_temp != 0)
		close(context->fd_temp);
	ft_close_multiple(context->pipe_cmd[0], context->pipe_cmd[1],
		block->fd_input, block->fd_output);
}

void	mult_redir_three(t_context *context, t_block *block)
{
	if (block->fd_output != 1)
		dup2(block->fd_output, STDOUT_FILENO);
	else
		dup2(context->pipe_cmd[1], STDOUT_FILENO);
	if (block->fd_input != 0)
		dup2(block->fd_input, STDIN_FILENO);
	else
		dup2(context->fd_temp, STDIN_FILENO);
	if (context->fd_temp != 0)
		close(context->fd_temp);
	ft_close_multiple(context->pipe_cmd[0], context->pipe_cmd[1],
		block->fd_input, block->fd_output);
}

void	redirect(t_context *context, t_block *block)
{
	if (block->cmd_number == 1)
		mult_redir_one(context, block);
	else if (block->cmd_number == context->nb_command)
		mult_redir_two(context, block);
	else
		mult_redir_three(context, block);
}

void	init_tab_pid(t_context *context)
{
	context->tab_pid = ft_calloc(context->nb_command, sizeof(pid_t));
	if (!context->tab_pid)
	{
		ft_free_loop(context);
		ft_free_garbage(context, 0);
		ft_free_all(context);
		exit(1);
	}
}
