/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:59 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:00 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signum;

void	end_multiple(t_context *context, int *status)
{
	int	nb;

	nb = 0;
	while (nb < context->nb_command)
	{
		waitpid(context->tab_pid[nb], status, WUNTRACED);
		nb++;
	}
}

void	get_multiple_exit(t_context *context, int *status)
{
	close(context->pipe_cmd[0]);
	if (WIFEXITED(*status) != 0)
	{
		context->exit_code = WEXITSTATUS(*status);
	}
	else if (WIFSIGNALED(*status))
		context->exit_code = WTERMSIG(*status) + 128;
	g_signum = 0;
}

void	no_mult_args(t_context *context, t_block *block)
{
	if (block->cmd_args[0] == NULL)
	{
		ft_close_multiple(context->pipe_cmd[0], context->pipe_cmd[1],
			block->fd_input, block->fd_output);
		ft_free_loop(context);
		ft_free_garbage(context, 0);
		ft_free_all(context);
		exit (0);
	}
}

void	abs_mult_path(t_context *context, t_block *block)
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

void	init_multiple_command(t_context *context)
{
	g_signum = 1;
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, signal_cmd);
	pipe(context->pipe_cmd);
	if (pipe < 0)
	{
		perror("pipe :");
		ft_free_loop(context);
		ft_free_garbage(context, 0);
		ft_free_all(context);
		exit (1);
	}
}
