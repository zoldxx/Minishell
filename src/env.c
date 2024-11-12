/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:50:30 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:50:31 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envlist_to_tab(t_context *context)
{
	int		i;
	char	*temp;
	char	*temp2;
	t_elist	*templist;

	i = 0;
	templist = context->env;
	if (context->env_tab)
		ft_free_tab(context->env_tab);
	context->env_tab = ft_malloc_double(context, ft_elstsize(context->env) + 1);
	while (templist)
	{
		temp = ft_ministrjoin(context, templist->content[0], "=");
		temp2 = ft_ministrjoin(context, temp, templist->content[1]);
		free(temp);
		context->env_tab[i] = temp2;
		i++;
		templist = templist->next;
	}
	context->env_tab[i] = NULL;
}

void	utils_strcpy_without_quote(char *src, char *dest, int *i, int *k)
{
	while (!is_quoted(src[*i], 0) && src[*i])
	{
		dest[*k] = src[*i];
		*i += 1;
		*k += 1;
	}
}

char	*strcpy_whithout_quote(char *src, char *dest)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (src[i])
	{
		utils_strcpy_without_quote(src, dest, &i, &k);
		if (src[i])
			i++;
		else
			break ;
		while (is_quoted(src[i], 0) && src[i])
		{
			dest[k] = src[i];
			i++;
			k++;
		}
	}
	dest[k] = '\0';
	return (is_quoted('a', 1), dest);
}

// char	**split_key_value_suite(char **kv, char *str, int ii, int jj)
// {
// 	int	i;
// 	int	j;

// 	i = ii;
// 	j = jj;
// 	while (j != i)
// 	{
// 		kv[0][j] = str[j];
// 		j++;
// 	}
// 	kv[0][j] = '\0';
// 	j++;
// 	while (str[i] != '\0')
// 		i++;
// 	kv[1] = ft_malloc(context, i - j + 1);
// 	i = 0;
// 	while (str[j])
// 	{
// 		kv[1][i] = str[j];
// 		i++;
// 		j++;
// 	}
// 	kv[1][i] = '\0';
// 	kv[2] = NULL;
// 	return (kv);
// }

char	**split_key_value_suite(char **kv, char *str,
	int *k, t_context *context)
{
	int	i;
	int	j;

	i = k[0];
	j = k[1];
	while (j != i)
	{
		kv[0][j] = str[j];
		j++;
	}
	kv[0][j] = '\0';
	j++;
	while (str[i] != '\0')
		i++;
	kv[1] = ft_malloc(context, i - j + 1);
	i = 0;
	while (str[j])
	{
		kv[1][i] = str[j];
		i++;
		j++;
	}
	kv[1][i] = '\0';
	kv[2] = NULL;
	return (kv);
}

char	**split_key_value(t_context *context, char *str)
{
	char	**kv;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	kv = ft_malloc_double(context, 3);
	while (str && str[i[0]])
	{
		if (str[i[0]] == '=' && !is_quoted(str[i[0]], 0))
			break ;
		i[0]++;
	}
	if (!str[i[0]])
		return (malloc_empty_value(context, kv, str));
	kv[0] = ft_malloc(context, i[0] + 1);
	return (split_key_value_suite(kv, str, i, context));
}

// char	**split_key_value(t_context *context, char *str)
// {
// 	char	**kv;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	kv = ft_malloc_double(context, 3);
// 	while (str && str[i])
// 	{
// 		if (str[i] == '=' && !is_quoted(str[i], 0))
// 			break ;
// 		i++;
// 	}
// 	if (!str[i])
// 		return (malloc_empty_value(context, kv, str));
// 	kv[0] = ft_malloc(context, i + 1);
// 	return (split_key_value_suite(kv, str, i, j));
// }

// char	**split_key_value(char *str)
// {
// 	char	**kv;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = -1;
// 	kv = ft_malloc_double(3);
// 	while (str && str[++i])
// 	{
// 		if (str[i] == '=' && !is_quoted(str[i], 0))
// 			break ;
// 	}
// 	if (!str[i])
// 		return (malloc_empty_value(kv, str));
// 	kv[0] = ft_malloc(i + 1);
// 	while (++j != i)
// 		kv[0][j] = str[j];
// 	kv[0][j] = '\0';
// 	j++;
// 	while (str[i] != '\0')
// 		i++;
// 	kv[1] = ft_malloc(i - j + 1);
// 	i = 0;
// 	while (str[j])
// 	{
// 		kv[1][i] = str[j];
// 		i++;
// 		j++;
// 	}
// 	kv[1][i] = '\0';
// 	kv[2] = NULL;
// 	return (kv);
// }

// char	**maloc(void)
// {
// 	char	**kv;

// 	kv = malloc(sizeof(char *) * 3);
// 	if (!kv)
// 		return (NULL);
// 	return (kv);
// }

// char	**split_key_value(char *str)
// {
// 	char	**kv;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	kv = maloc();
// 	while (str && str[i])
// 	{
// 		if (str[i] == '=' && !is_quoted(str[i], 0))
// 			break ;
// 		i++;
// 	}
// 	kv[0] = malloc(sizeof(char) * (i + 1));
// 	if (!kv[0])
// 		return (NULL);
// 	if (!str[i])
// 	{
// 		free(kv[0]);
// 		kv[0] = malloc(ft_strlen(str) + 1);
// 		kv[0] = ft_strcpy(kv[0], str);
// 		kv[1] = NULL;
// 		kv[2] = NULL;
// 		return (kv);
// 	}
// 	while (j != i)
// 	{
// 		kv[0][j] = str[j];
// 		j++;
// 	}
// 	kv[0][j] = '\0';
// 	j++;
// 	while (str[i] != '\0')
// 		i++;
// 	kv[1] = malloc(sizeof(char) * (i - j + 1));
// 	if (!kv[1])
// 		return (NULL);
// 	i = 0;
// 	while (str[j])
// 	{
// 		kv[1][i] = str[j];
// 		i++;
// 		j++;
// 	}
// 	kv[1][i] = '\0';
// 	kv[2] = NULL;
// 	return (kv);
// }

// char	*strcpy_whithout_quote(char *src, char *dest)
// {
// 	int	i;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	while (src[i])
// 	{
// 		while (!is_quoted(src[i], 0) && src[i])
// 		{
// 			dest[k] = src[i];
// 			i++;
// 			k++;
// 		}
// 		if (src[i])
// 			i++;
// 		else
// 			break ;
// 		while (is_quoted(src[i], 0) && src[i])
// 		{
// 			dest[k] = src[i];
// 			i++;
// 			k++;
// 		}
// 	}
// 	dest[k] = '\0';
// 	return (is_quoted('a', 1), dest);
// }
