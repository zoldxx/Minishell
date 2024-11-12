/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:36 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:37 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_values(t_context *context)
{
	context->input_line = NULL;
	context->garbage = NULL;
	context->fd_temp = 0;
	context->block = NULL;
	context->env = NULL;
	context->hide_env = NULL;
	context->path_list = NULL;
	context->my_path = NULL;
	context->tab_block = NULL;
	context->nb_command = 0;
	context->env_tab = NULL;
	context->heredoc_nb = 1;
	context->exit_code = 0;
	context->is_created = 1;
	context->tab_pid = NULL;
}

void	get_env(t_context *context, char **envp)
{
	int		i;
	t_elist	*tmp;

	i = -1;
	if (!envp[0])
		return ;
	while (envp && envp[++i])
	{
		tmp = ft_elstnew(context, split_key_value(context, envp[i]));
		ft_elstadd_back(&(context->env), tmp);
	}
	ft_envlist_to_tab(context);
	init_hide_env(context);
}

void	get_path(t_context *context)
{
	int		i;
	t_elist	*temp;

	temp = context->env;
	context->my_path = NULL;
	if (context->path_list)
	{
		ft_free_list_content(context->path_list);
		ft_free_list(context->path_list);
		context->path_list = NULL;
	}
	while (temp)
	{
		if (!ft_strncmp(temp->content[0], "PATH", 4))
		{
			context->my_path = ft_minisplit(context, temp->content[1], ':');
			break ;
		}
		temp = temp->next;
	}
	i = -1;
	while (context->my_path && context->my_path[++i])
		ft_lstadd_back(&(context->path_list), fm(context, context->my_path[i]));
	if (context->my_path)
		free(context->my_path);
}

void	init(t_context *context, char **envp)
{
	init_values(context);
	get_env(context, envp);
	get_path(context);
}

void	ft_init_loop(t_context *context)
{
	context->is_created = 1;
	context->block = NULL;
	context->tab_block = NULL;
	context->nb_command = 0;
}
