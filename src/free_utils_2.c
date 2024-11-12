/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:15 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:16 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list_content(t_list *list)
{
	while (list)
	{
		if (list->content)
		{
			free(list->content);
			list->content = NULL;
		}
		list = list->next;
	}
}

void	ft_free_redirlist_content(t_redir *list)
{
	while (list)
	{
		if (list->filename)
		{
			free(list->filename);
			list->filename = NULL;
		}
		list = list->next;
	}
}

void	ft_free_elist_content(t_elist *list)
{
	while (list)
	{
		if (list->content)
		{
			if (list->content[0])
			{
				free(list->content[0]);
				list->content[0] = NULL;
			}
			if (list->content[1])
			{
				free(list->content[1]);
				list->content[1] = NULL;
			}
			free(list->content);
			list->content = NULL;
		}
		list = list->next;
	}
}

void	ft_free_list(t_list *list)
{
	t_list	*temp;

	temp = NULL;
	if (list)
	{
		while (list)
		{
			temp = list->next;
			free(list);
			list = temp;
		}
		free(list);
		list = NULL;
	}
}

void	ft_free_redirlist(t_redir *list)
{
	t_redir	*temp;

	temp = NULL;
	if (list)
	{
		while (list)
		{
			temp = list->next;
			free(list);
			list = temp;
		}
		free(list);
	}
}
