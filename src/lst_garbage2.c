/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_garbage2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:47 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:48 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsizegarbage(t_garbage *garbage)
{
	int		size;

	size = 0;
	while (garbage)
	{
		size++;
		garbage = garbage->next;
	}
	return (size);
}

t_garbage	*ft_lstlastgarbage(t_garbage *lst)
{
	int			i;
	t_garbage	*temp;

	temp = lst;
	i = 0;
	while (i < ft_lstsizegarbage(lst) - 1)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}
