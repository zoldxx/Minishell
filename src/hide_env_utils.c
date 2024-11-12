/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:31 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:32 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	res;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	res = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (res);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

char	**ft_strdup_tab(t_context *context, char **s)
{
	char	**dup;

	dup = ft_malloc_double(context, 3);
	dup[0] = ft_malloc(context, ft_strlen(s[0]) + 1);
	dup[0] = ft_strcpy(dup[0], s[0]);
	dup[1] = ft_malloc(context, ft_strlen(s[1]) + 1);
	dup[1] = ft_strcpy(dup[1], s[1]);
	dup[2] = NULL;
	return (dup);
}

void	tout_pour_la_norm(t_context *context, t_elist *copy)
{
	ft_elstadd_back(&(context->hide_env), ft_elstnew(context, copy->content));
	free(copy);
}
