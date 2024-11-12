/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:40 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:41 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_block	*ft_lstnewblock(t_context *context, void *content)
{
	t_block	*new;

	new = malloc(sizeof(t_block));
	if (!new)
		ft_free_garbage(context, 1);
	new->cmd_list = NULL;
	new->redir_list = NULL;
	new->fd_input = 0;
	new->fd_output = 1;
	new->fd_here = 0;
	new->block_line = content;
	new->next = NULL;
	new->launch_exec = 1;
	new->cmd_args = NULL;
	new->fail_malloc = 0;
	new->cmd_expand = NULL;
	new->expand = NULL;
	new->exp_redir = NULL;
	new->context = context;
	return (new);
}

int	ft_lstsizeblock(t_block *block)
{
	int		size;

	size = 0;
	while (block)
	{
		size++;
		block = block->next;
	}
	return (size);
}

t_block	*ft_lstlastblock(t_block *lst)
{
	int		i;
	t_block	*temp;

	temp = lst;
	i = 0;
	while (i < ft_lstsizeblock(lst) - 1)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

void	ft_lstadd_backblock(t_block **lst, t_block *new)
{
	if (*lst == 0)
		*lst = new;
	else
		ft_lstlastblock(*lst)->next = new;
}
