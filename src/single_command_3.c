/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:27 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:28 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signum;

int	get_single_exit(t_context *context, int status)
{
	g_signum = 0;
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, signal_cmd);
	if (WIFEXITED(status) != 0)
		context->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_signum = WTERMSIG(status) + 128;
		if (g_signum == 130)
			return (1);
		else if (g_signum == 131)
			return (2);
	}
	return (0);
}

void	single_parent_process(t_context *context)
{
	if (context->block->fd_input != 0)
		close(context->block->fd_input);
	if (context->block->fd_output != 1)
		close(context->block->fd_output);
}

void	no_single_args(t_context *context, t_block *block)
{
	if (block->cmd_args[0] == NULL)
	{
		if (block->fd_input > 0)
			close(block->fd_input);
		if (block->fd_output > 1)
			close(block->fd_output);
		ft_free_loop(context);
		ft_free_garbage(context, 0);
		ft_free_all(context);
		exit (0);
	}
}

void	abs_single_path(t_context *context, t_block *block)
{
	if (access(block->cmd_args[0], F_OK) == 0)
	{
		if (access(block->cmd_args[0], X_OK) == -1)
		{
			perror(block->cmd_args[0]);
			ft_free_loop(context);
			ft_free_garbage(context, 0);
			ft_free_all(context);
			exit (126);
		}
		execve(block->cmd_args[0], block->cmd_args, context->env_tab);
	}
}
