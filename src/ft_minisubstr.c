/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisubstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:26 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:27 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_miniinitmal(t_context *context, char const *s,
	unsigned int start, size_t len)
{
	char	*res;

	if (len > ft_strlen(s) - start)
		res = ft_malloc(context, ft_strlen(s) - start + 1);
	else
	{
		if (len <= ft_strlen(s))
			res = ft_malloc(context, (len + 1));
		else
			res = ft_malloc(context, (ft_strlen(s) + 1));
	}
	if (!res)
		return (0);
	return (res);
}

char	*ft_miniboucle(char const *s, unsigned int start, size_t len, char *res)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start)
		{
			if (s[i] && j < len)
			{
				res[j] = s[i];
				j++;
			}
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_minisubstr(t_context *context,
	char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		res = ft_malloc(context, 1);
		res[0] = '\0';
		return (res);
	}
	res = ft_miniinitmal(context, s, start, len);
	res = ft_miniboucle(s, start, len, res);
	return (res);
}
