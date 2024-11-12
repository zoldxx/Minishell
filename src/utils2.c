/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:50 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:51 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_ministrdup(t_context *context, const char *s)
{
	int		len;
	char	*dup;

	len = 0;
	while (s[len])
		len++;
	dup = ft_malloc(context, len + 1);
	if (!dup)
		return (0);
	len = 0;
	while (s[len])
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_ministrjoin(t_context *context, char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	char	*res;

	size1 = 0;
	size2 = 0;
	if (!s1 || !s2)
		return (ft_ministrdup(context, ""));
	res = ft_malloc(context, ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[size1])
	{
		res[size1] = s1[size1];
		size1++;
	}
	while (s2[size2])
	{
		res[size1 + size2] = s2[size2];
		size2++;
	}
	res[size1 + size2] = '\0';
	return (res);
}

t_list	*fm(t_context *context, void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		ft_free_garbage(context, 1);
	new->content = content;
	new->next = 0;
	return (new);
}
