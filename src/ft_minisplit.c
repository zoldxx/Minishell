/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:24 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:25 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_nbstring(char const *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			res += 1;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (res);
}

int	ft_lentemp(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	ft_free(char **res, int index)
{
	while (index >= 0)
	{
		free(res[index]);
		index--;
	}
	free(res);
}

char	**ft_minit(t_context *context, char const *s, char c)
{
	char	**res;

	if (!s)
		return (0);
	res = ft_malloc_double(context, (ft_nbstring(s, c) + 1));
	if (!res)
		return (0);
	return (res);
}

char	**ft_minisplit(t_context *context, char const *s, char c)
{
	int		index;
	char	*temp;
	char	**res;

	index = 0;
	res = ft_minit(context, s, c);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s == '\0')
			break ;
		temp = ft_minisubstr(context, s, 0, ft_lentemp(s, c));
		if (!temp)
		{
			ft_free(res, index - 1);
			return (0);
		}
		res[index] = temp;
		index++;
		while (*s != '\0' && *s != c)
			s++;
	}
	res[index] = 0;
	return (res);
}
