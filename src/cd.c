/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:12 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:13 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_pwd(t_context *context, char *pwd)
{
	int		i;
	char	*key_pwd;

	if (!pwd)
		return (NULL);
	i = 0;
	key_pwd = ft_malloc(context, (ft_strlen(pwd) + 5));
	key_pwd[0] = 'P';
	key_pwd[1] = 'W';
	key_pwd[2] = 'D';
	key_pwd[3] = '=';
	while (pwd[i])
	{
		key_pwd[i + 4] = pwd[i];
		i++;
	}
	key_pwd[i + 4] = '\0';
	return (key_pwd);
}

char	*copy_oldpwd(t_context *context, char *pwd)
{
	int		i;
	char	*key_pwd;

	if (!pwd)
		return (NULL);
	i = 0;
	key_pwd = ft_malloc(context, (ft_strlen(pwd) + 8));
	key_pwd[0] = 'O';
	key_pwd[1] = 'L';
	key_pwd[2] = 'D';
	key_pwd[3] = 'P';
	key_pwd[4] = 'W';
	key_pwd[5] = 'D';
	key_pwd[6] = '=';
	while (pwd[i])
	{
		key_pwd[i + 7] = pwd[i];
		i++;
	}
	key_pwd[i + 7] = '\0';
	return (key_pwd);
}

int	update_pwd(t_context *context, char *pwd)
{
	char	*key_pwd;
	char	*key_old_pwd;

	if (!pwd)
		return (0);
	key_old_pwd = copy_oldpwd(context, pwd);
	if (key_old_pwd)
		ft_modify_value_export(context, key_old_pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50);
	key_pwd = copy_pwd(context, pwd);
	if (key_pwd)
		ft_modify_value_export(context, key_pwd);
	free(pwd);
	pwd = NULL;
	free(key_pwd);
	key_pwd = NULL;
	free(key_old_pwd);
	key_old_pwd = NULL;
	return (0);
}

void	end_cd(t_context *context, char *pwd)
{
	if (is_in_hide_env(context, "PWD") && !is_in_env(context, "PWD="))
		ft_elstadd_back(&(context->env), ft_elstnew(context,
				split_key_value(context, "PWD")));
	else if (!is_in_hide_env(context, "PWD")
		&& !is_in_env(context, "PWD="))
		if_export(context, copy_pwd(context, pwd));
	if (is_in_hide_env(context, "OLDPWD") && !is_in_env(context, "OLDPWD="))
		ft_elstadd_back(&(context->env), ft_elstnew(context,
				split_key_value(context, "OLDPWD")));
	else if (!is_in_hide_env(context, "OLDPWD")
		&& !is_in_env(context, "OLDPWD="))
		if_export(context, copy_oldpwd(context, pwd));
	update_pwd(context, pwd);
}

int	ft_cd(t_context *context, t_block *block)
{
	char	*pwd;

	(void)context;
	if (block->cmd_args[1] == NULL)
		return (0);
	if (block->cmd_args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		context->exit_code = 1;
	}
	pwd = getcwd(NULL, 0);
	if (errno != ENOENT && pwd == NULL)
	{
		context->exit_code = 50;
		return (50);
	}
	if (chdir(block->cmd_args[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(block->cmd_args[1]);
		context->exit_code = 1;
		return (free(pwd), 50);
	}
	end_cd(context, pwd);
	return (0);
}

// int	ft_cd(t_context *context, t_block *block)
// {
// 	char	*pwd;

// 	(void)context;
// 	if (block->cmd_args[1] == NULL)
// 		return (0);
// 	if (block->cmd_args[2])
// 	{
// 		ft_putstr_fd("cd: too many arguments\n", 2);
// 		context->exit_code = 1;
// 	}
// 	pwd = getcwd(NULL, 0);
// 	if (errno != ENOENT && pwd == NULL)
// 	{
// 		context->exit_code = 50;
// 		return (50);
// 	}
// 	if (chdir(block->cmd_args[1]) == -1)
// 	{
// 		ft_putstr_fd("cd: ", 2);
// 		perror(block->cmd_args[1]);
// 		context->exit_code = 1;
// 		return (free(pwd), 50);
// 	}
// 	if (is_in_hide_env(context, "PWD") && !is_in_env(context, "PWD="))
// 		ft_elstadd_back(&(context->env), ft_elstnew(split_key_value(context,
//						"PWD")));
// 	if (is_in_hide_env(context, "OLDPWD") && !is_in_env(context, "OLDPWD="))
// 		ft_elstadd_back(&(context->env), ft_elstnew(split_key_value(context,
//						"OLDPWD")));
// 	update_pwd(context, pwd);
// 	return (0);
// }
