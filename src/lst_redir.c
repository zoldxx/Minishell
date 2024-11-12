/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:49 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:50 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*ft_lstnewredir(t_context *context, char *content, int redir_type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		ft_free_garbage(context, 1);
	new->filename = content;
	new->redir_type = redir_type;
	new->next = NULL;
	return (new);
}

int	ft_lstsizeredir(t_redir *redir)
{
	int		size;

	size = 0;
	while (redir)
	{
		size++;
		redir = redir->next;
	}
	return (size);
}

t_redir	*ft_lstlastredir(t_redir *lst)
{
	int		i;
	t_redir	*temp;

	temp = lst;
	i = 0;
	while (i < ft_lstsizeredir(lst) - 1)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

void	ft_lstadd_backredir(t_redir **lst, t_redir *new)
{
	if (*lst == 0)
		*lst = new;
	else
		ft_lstlastredir(*lst)->next = new;
}
