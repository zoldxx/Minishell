/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:33 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:34 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signum;

void	ft_close_here(t_context	*context, t_block *block)
{
	t_block	*temp_block;

	temp_block = context->block;
	while (temp_block != block)
	{
		if (temp_block->fd_here > 0)
			close(temp_block->fd_here);
		temp_block = temp_block->next;
	}
}

void	launch_heredocs_process(t_context *context, t_block *block,
	t_redir *redir)
{
	int		status;
	pid_t	parent;

	status = 0;
	if (block->fd_here != 0)
		close(block->fd_here);
	init_heredoc(context, &parent);
	if (!parent)
	{
		signal(SIGINT, signal_cmd);
		close(context->heredoc_pipe[0]);
		ft_close_here(context, block);
		ft_wr_heredoc(context, block, redir);
	}
	else
		close(context->heredoc_pipe[1]);
	waitpid(parent, &status, 0);
	if (WIFEXITED(status) != 0)
		g_signum = WEXITSTATUS(status);
	block->fd_here = context->heredoc_pipe[0];
}

int	end_heredoc(t_context *context)
{
	if (g_signum > 2)
	{
		context->exit_code = g_signum;
		g_signum = 0;
		return (1);
	}
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, signal_cmd);
	g_signum = 0;
	return (0);
}

int	ft_open_heredocs(t_context *context)
{
	t_block	*block;
	t_redir	*redir;

	block = context->block;
	g_signum = 2;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (block)
	{
		redir = block->redir_list;
		while (redir)
		{
			if (redir->redir_type == 3)
				launch_heredocs_process(context, block, redir);
			redir = redir->next;
		}
		block->fd_input = 0;
		block = block->next;
	}
	if (end_heredoc(context) == 1)
		return (1);
	return (0);
}

void	launch_exec(t_context *context)
{
	int	nb;

	get_path(context);
	if (context->nb_command == 1)
	{
		nb = single_command(context);
		if (nb == 1)
		{
			context->exit_code = g_signum;
			g_signum = 0;
			ft_putstr_fd("\n", 2);
		}
		else if (nb == 2)
		{
			context->exit_code = g_signum;
			g_signum = 0;
			write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		}
	}
	else
		multiple_command(context);
}
