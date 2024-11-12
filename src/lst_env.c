/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:43 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:44 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elist	*ft_elstnew(t_context *context, char **content)
{
	t_elist	*new;

	new = malloc(sizeof(t_elist));
	if (!new)
		ft_free_garbage(context, 1);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_elstsize(t_elist *lst)
{
	int		size;
	t_elist	*temp;

	temp = lst;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

t_elist	*ft_elstlast(t_elist *lst)
{
	int		i;
	t_elist	*temp;

	temp = lst;
	i = 0;
	while (i < ft_elstsize(lst) - 1)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

void	ft_elstadd_back(t_elist **lst, t_elist *new)
{
	if (*lst == 0)
		*lst = new;
	else
		ft_elstlast(*lst)->next = new;
}

void	ft_elstadd_front(t_elist **lst, t_elist *new)
{
	t_elist	*temp;

	temp = *lst;
	*lst = new;
	new->next = temp;
}
