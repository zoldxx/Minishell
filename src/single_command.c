/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:30 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:31 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signum;

void	single_child_process(t_context *context, t_block *block)
{
	char	*cmd;
	char	*tempchar;
	t_list	*temp;
	int		i;

	i = -1;
	temp = context->path_list;
	no_single_args(context, block);
	abs_single_path(context, block);
	while (temp)
	{
		tempchar = ft_ministrjoin(context, temp->content, "/");
		cmd = ft_ministrjoin(context, tempchar, block->cmd_args[0]);
		free(tempchar);
		execve(cmd, block->cmd_args, context->env_tab);
		free(cmd);
		temp = temp->next;
	}
	ft_putstr_fd(block->cmd_args[0], 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	ft_free_loop(context);
	ft_free_garbage(context, 0);
	ft_free_all(context);
	exit (127);
}

void	single_redirect(t_context *context)
{
	if (context->block->fd_input > 0)
		dup2(context->block->fd_input, STDIN_FILENO);
	if (context->block->fd_output > 1)
		dup2(context->block->fd_output, STDOUT_FILENO);
	ft_close_single(context->block->fd_input, context->block->fd_output);
}

void	launch_single_child(t_context *context)
{
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, signal_cmd);
	single_redirect(context);
	single_child_process(context, context->block);
}

void	launch_single_no_built(t_context *context, pid_t parent)
{
	g_signum = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	parent = fork();
	if (parent < 0)
	{
		perror("fork: ");
		ft_free_loop(context);
		ft_free_garbage(context, 0);
		ft_free_all(context);
		exit (1);
	}
	if (!parent)
		launch_single_child(context);
	else
		single_parent_process(context);
}

int	single_command(t_context *context)
{
	pid_t	parent;
	int		status;
	int		get_exit;

	get_exit = 0;
	parent = (pid_t)0;
	status = 1;
	if (context->block->launch_exec == 1
		&& ft_open_single_redir(context, context->block) != 1)
	{
		if (is_builtin(context, context->block) == 0)
			launch_single_no_built(context, parent);
		else
			single_parent_process(context);
		waitpid(parent, &status, 0);
		get_exit = get_single_exit(context, status);
		if (get_exit == 1)
			return (1);
		else if (get_exit == 2)
			return (2);
	}
	else
		context->exit_code = 1;
	g_signum = 0;
	return (0);
}
