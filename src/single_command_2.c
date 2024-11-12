/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:25 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:26 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_single(int fd_in, int fd_out)
{
	if (fd_in > 0)
		close(fd_in);
	if (fd_out > 1)
		close(fd_out);
}

int	error_single_open(t_block *block, t_redir *redir)
{
	if (block->fd_input == -1 || block->fd_output == -1)
	{
		if (redir->redir_type != 3)
			perror(redir->filename);
		ft_close_single(block->fd_input, block->fd_output);
		return (1);
	}
	return (0);
}

int	manage_single_in(t_block *block, t_redir *redir)
{
	if (redir->redir_type == 1)
	{
		if (block->fd_input > 0 && block->fd_input != block->fd_here)
			close(block->fd_input);
		block->fd_input = open(redir->filename, O_RDONLY);
		if (error_single_open(block, redir) == 1)
			return (1);
	}
	else if (redir->redir_type == 3)
	{
		if (block->fd_input > 0 && block->fd_input != block->fd_here)
			close(block->fd_input);
		block->fd_input = block->fd_here;
		if (error_single_open(block, redir) == 1)
			return (1);
	}
	return (0);
}

int	manage_single_out(t_block *block, t_redir *redir)
{
	if (redir->redir_type == 2)
	{
		if (block->fd_output > 1)
			close(block->fd_output);
		block->fd_output = open(redir->filename,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (error_single_open(block, redir) == 1)
			return (1);
	}
	else if (redir->redir_type == 4)
	{
		if (block->fd_output != 1)
			close(block->fd_output);
		block->fd_output = open(redir->filename,
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (error_single_open(block, redir) == 1)
			return (1);
	}
	return (0);
}

int	ft_open_single_redir(t_context *context, t_block *block)
{
	t_redir	*redir;

	(void)context;
	redir = block->redir_list;
	while (redir)
	{
		if (redir->redir_type == 1 && manage_single_in(block, redir))
			return (1);
		else if (redir->redir_type == 2 && manage_single_out(block, redir))
			return (1);
		else if (redir->redir_type == 3 && manage_single_in(block, redir))
			return (1);
		else if (redir->redir_type == 4 && manage_single_out(block, redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
