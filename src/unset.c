/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:45 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:46 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	boucle_unset(t_elist *temp, t_block *block, t_elist *tmp, int i)
{
	while (temp && temp->next)
	{
		if (temp && !ft_strcmp(block->cmd_args[i],
				temp->next->content[0]))
		{
			tmp = temp->next->next;
			free(temp->next->content[0]);
			if (temp->next->content[1])
				free(temp->next->content[1]);
			free(temp->next->content);
			free(temp->next);
			temp->next = tmp;
			break ;
		}
		else
			temp = temp->next;
	}
}

void	ft_unset_env(t_context *context, t_block *block)
{
	t_elist	*tmp;
	t_elist	*temp;
	int		i;

	temp = context->env;
	i = 0;
	if (temp)
	{
		while (block->cmd_args[++i])
		{
			if (temp && !ft_strcmp(block->cmd_args[i], temp->content[0]))
			{
				tmp = temp->next;
				free(temp->content[0]);
				if (temp->content[1])
					free(temp->content[1]);
				free(temp->content);
				free(temp);
				context->env = tmp;
			}
			else
				boucle_unset(temp, block, tmp, i);
			temp = context->env;
		}
	}
}

void	ft_unset_hide(t_context *context, t_block *block)
{
	t_elist	*tmp;
	t_elist	*temp;
	int		i;

	temp = context->hide_env;
	i = 0;
	if (temp)
	{
		while (block->cmd_args[++i])
		{
			if (temp && !ft_strcmp(block->cmd_args[i], temp->content[0]))
			{
				tmp = temp->next;
				free(temp->content[0]);
				if (temp->content[1])
					free(temp->content[1]);
				free(temp->content);
				free(temp);
				context->hide_env = tmp;
			}
			else
				boucle_unset(temp, block, tmp, i);
			temp = context->hide_env;
		}
	}
}

void	ft_unset(t_context *context, t_block *block)
{
	ft_unset_env(context, block);
	ft_unset_hide(context, block);
	ft_envlist_to_tab(context);
	context->exit_code = 0;
}

// void	ft_unset_hide(t_context *context, t_block *block)
// {
// 	t_elist	*tmp;
// 	t_elist	*temp;
// 	int		i;

// 	temp = context->hide_env;
// 	i = 0;
// 	if (temp)
// 	{
// 		while (block->cmd_args[++i])
// 		{
// 			if (temp && !ft_strcmp(block->cmd_args[i], temp->content[0]))
// 			{
// 				tmp = temp->next;
// 				free(temp->content[0]);
// 				if (temp->content[1])
// 					free(temp->content[1]);
// 				free(temp->content);
// 				free(temp);
// 				context->hide_env = tmp;
// 			}
// 			else
// 			{
// 				while (temp && temp->next)
// 				{
// 					if (temp && !ft_strcmp(block->cmd_args[i],
// 							temp->next->content[0]))
// 					{
// 						tmp = temp->next->next;
// 						free(temp->next->content[0]);
// 						if (temp->next->content[1])
// 							free(temp->next->content[1]);
// 						free(temp->next->content);
// 						free(temp->next);
// 						temp->next = tmp;
// 						break ;
// 					}
// 					else
// 						temp = temp->next;
// 				}
// 			}
// 			temp = context->hide_env;
// 		}
// 	}
// }

// void	ft_unset(t_context *context, t_block *block)
// {
// 	t_elist	*tmp;
// 	t_elist	*temp;
// 	int		i;

// 	temp = context->env;
// 	i = 0;
// 	if (temp)
// 	{
// 		while (block->cmd_args[++i])
// 		{
// 			if (temp && !ft_strcmp(block->cmd_args[i], temp->content[0]))
// 			{
// 				tmp = temp->next;
// 				free(temp->content[0]);
// 				if (temp->content[1])
// 					free(temp->content[1]);
// 				free(temp->content);
// 				free(temp);
// 				context->env = tmp;
// 			}
// 			else
// 			{
// 				while (temp && temp->next)
// 				{
// 					if (temp && !ft_strcmp(block->cmd_args[i],
// 							temp->next->content[0]))
// 					{
// 						tmp = temp->next->next;
// 						free(temp->next->content[0]);
// 						free(temp->next->content[1]);
// 						free(temp->next->content);
// 						free(temp->next);
// 						temp->next = tmp;
// 						break ;
// 					}
// 					else
// 						temp = temp->next;
// 				}
// 			}
// 			temp = context->env;
// 		}
// 	}
// 	ft_unset_hide(context, block);
// 	ft_envlist_to_tab(context);
// }
