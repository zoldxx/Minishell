/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:37 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:38 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_context *context, t_block *block)
{
	int	value;

	value = 0;
	if (!ft_strcmp(block->cmd_args[0], "echo"))
		return (ft_echo(context, block), 1);
	if (!ft_strcmp(block->cmd_args[0], "cd"))
		return (ft_cd(context, block), 1);
	if (!ft_strcmp(block->cmd_args[0], "pwd"))
		return (ft_pwd(context), 1);
	if (!ft_strcmp(block->cmd_args[0], "export"))
		return (ft_export(context, block), 1);
	if (!ft_strcmp(block->cmd_args[0], "unset"))
		return (ft_unset(context, block), 1);
	if (!ft_strcmp(block->cmd_args[0], "env"))
		return (ft_env(context, block), 1);
	if (!ft_strcmp(block->cmd_args[0], "exit"))
		return (exit_process(context, block), 1);
	return (0);
}

int	only_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_without_n(t_context *context, t_block *block)
{
	int	i;

	i = 0;
	while (block->cmd_args[++i])
	{
		if (context->nb_command != 1)
		{
			ft_putstr_fd(block->cmd_args[i], 1);
			if (block->cmd_args[i + 1])
				ft_putstr_fd(" ", 1);
		}
		else
		{
			ft_putstr_fd(block->cmd_args[i], block->fd_output);
			if (block->cmd_args[i + 1])
				ft_putstr_fd(" ", block->fd_output);
		}
	}
	if (context->nb_command != 1)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd("\n", block->fd_output);
}

void	if_else_echo(t_context *context, t_block *block, int i)
{
	if (context->nb_command != 1)
	{
		ft_putstr_fd(block->cmd_args[i], 1);
		if (block->cmd_args[i + 1])
			ft_putstr_fd(" ", 1);
	}
	else
	{
		ft_putstr_fd(block->cmd_args[i], block->fd_output);
		if (block->cmd_args[i + 1])
			ft_putstr_fd(" ", block->fd_output);
	}
}

void	ft_echo(t_context *context, t_block *block)
{
	int	i;

	i = 0;
	if (block->cmd_args[1])
	{
		if (!ft_strncmp(block->cmd_args[1], "-n", 2)
			&& !only_n(block->cmd_args[1] + 2))
		{
			i++;
			while (block->cmd_args[++i])
				if_else_echo(context, block, i);
		}
		else
			echo_without_n(context, block);
	}
	else
		ft_putstr_fd("\n", 1);
	context->exit_code = 0;
}

// void	ft_echo(t_context *context, t_block *block)
// {
// 	int	i;

// 	i = 0;
// 	if (block->cmd_args[1])
// 	{
// 		if (!ft_strncmp(block->cmd_args[1], "-n", 2)
// 			&& !only_n(block->cmd_args[1] + 2))
// 		{
// 			i++;
// 			while (block->cmd_args[++i])
// 			{
// 				if (context->nb_command != 1)
// 				{
// 					ft_putstr_fd(block->cmd_args[i], 1);
// 					if (block->cmd_args[i + 1])
// 						ft_putstr_fd(" ", 1);
// 				}
// 				else
// 				{
// 					ft_putstr_fd(block->cmd_args[i], block->fd_output);
// 					if (block->cmd_args[i + 1])
// 						ft_putstr_fd(" ", block->fd_output);
// 				}
// 			}
// 		}
// 		else
// 			echo_without_n(context, block);
// 	}
// 	else
// 		ft_putstr_fd("\n", 1);
// 	context->exit_code = 0;
// }

// void	ft_echo(t_block *block)
// {
// 	int	i;

// 	i = 0;
// 	if (block->cmd_args[1])
// 	{
// 		if (!ft_strncmp(block->cmd_args[1], "-n", 2)
// 			&& !only_n(block->cmd_args[1] + 2))
// 		{
// 			i++;
// 			while (block->cmd_args[++i])
// 			{
// 				ft_putstr_fd(block->cmd_args[i], block->fd_output);
// 				if (block->cmd_args[i + 1])
// 					ft_putstr_fd(" ", block->fd_output);
// 			}
// 		}
// 		else
// 		{
// 			while (block->cmd_args[++i])
// 			{
// 				ft_putstr_fd(block->cmd_args[i], block->fd_output);
// 				if (block->cmd_args[i + 1])
// 					ft_putstr_fd(" ", block->fd_output);
// 			}
// 			ft_putstr_fd("\n", block->fd_output);
// 		}
// 	}
// 	else
// 		ft_putstr_fd("\n", block->fd_output);
// 	return ;
// }
