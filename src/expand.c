/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:08 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:09 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int	value_existe(t_context *context, char *str, int i, int j)
// {
// 	t_elist	*env;

// 	env = context->env;
// 	if (i - j == 0)
// 		return (2);
// 	while (env)
// 	{
// 		if (!ft_strncmp(env->content[0], str + j, i - j) && i
// 			- j == (int)ft_strlen(env->content[0]))
// 			return (1);
// 		env = env->next;
// 	}
// 	return (0);
// }

// int	*size_key(char *str, int nb_dollar)
// {
// 	int	*size_key;
// 	int	i;
// 	int	j;
// 	int	quote;

// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	size_key = malloc(sizeof(int) * nb_dollar);
// 	if (!size_key)
// 		return (NULL);
// 	nb_dollar = 0;
// 	while (str[i])
// 	{
// 		quote = is_quoted(str[i], 0);
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			j = i;
// 			if (str[i] != '?')
// 			{
// 				while (str[i] && (str[i] != '$' && str[i] != ' '
// 						&& str[i] != '\t' && str[i] != '\'' && str[i] != '\"'))
// 					i++;
// 				size_key[nb_dollar] = i - j;
// 			}
// 			else
// 				size_key[nb_dollar] = 1;
// 			nb_dollar++;
// 		}
// 		else
// 			i++;
// 	}
// 	is_quoted(str[i], 1);
// 	return (size_key);
// }

// int	*is_expendable(t_context *context, char *str, int nb_dollar)
// {
// 	int	*tab_dollar;
// 	int	i;
// 	int	j;
// 	int	quote;

// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	tab_dollar = malloc(sizeof(int) * nb_dollar);
// 	if (!tab_dollar)
// 		return (NULL);
// 	nb_dollar = 0;
// 	while (str[i])
// 	{
// 		quote = is_quoted(str[i], 0);
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			j = i;
// 			if (str[i] != '?')
// 			{
// 				while (str[i] && (str[i] != '$' && str[i] != ' '
// 						&& str[i] != '\t' && str[i] != '\'' && str[i] != '\"'))
// 					i++;
// 			}
// 			if (quote == 1)
// 				tab_dollar[nb_dollar] = 1;
// 			else
// 			{
// 				if (str[i] == '?')
// 					tab_dollar[nb_dollar] = 3;
// 				else if (value_existe(context, str, i, j) == 1)
// 					tab_dollar[nb_dollar] = 2;
// 				else if (value_existe(context, str, i, j) == 2)
// 					tab_dollar[nb_dollar] = 0;
// 				else
// 					tab_dollar[nb_dollar] = 0;
// 			}
// 			nb_dollar++;
// 		}
// 		else
// 			i++;
// 	}
// 	is_quoted(str[i], 1);
// 	return (tab_dollar);
// }

// int	count_dollar(char *str)
// {
// 	int	i;
// 	int	nb_dollar;

// 	i = 0;
// 	nb_dollar = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			nb_dollar++;
// 		i++;
// 	}
// 	return (nb_dollar);
// }

// int	nb_quotes(char *str)
// {
// 	int	i;
// 	int	nb;
// 	int	quote;
// 	int	rentre;

// 	i = 0;
// 	nb = 0;
// 	quote = 0;
// 	while (str[i])
// 	{
// 		rentre = 0;
// 		while (str[i] && quote == 0)
// 		{
// 			quote = is_quoted(str[i], 0);
// 			i++;
// 		}
// 		while (str[i] && quote != 0)
// 		{
// 			quote = is_quoted(str[i], 0);
// 			i++;
// 			rentre = 1;
// 		}
// 		if (rentre == 1)
// 			nb += 2;
// 	}
// 	return (nb);
// }

// int	value_size(t_context *context, char *str, int i, int j)
// {
// 	t_elist	*env;

// 	(void)i;
// 	env = context->env;
// 	while (env)
// 	{
// 		if (!ft_strncmp(env->content[0], str + j, i - j) && i
// 			- j == (int)ft_strlen(env->content[0]))
// 			return (ft_strlen(env->content[1]));
// 		env = env->next;
// 	}
// 	return (0);
// }

// int	nb_char_interr(t_context *context)
// {
// 	int	res;
// 	int	nb;

// 	res = 0;
// 	nb = context->exit_code;
// 	if (nb == 0)
// 		return (1);
// 	while (nb > 0)
// 	{
// 		res++;
// 		nb = nb / 10;
// 	}
// 	return (res);
// }

// int	calcul_len(t_context *context, int *tab_dollar, char *str)
// {
// 	int	len_final;
// 	int	i;
// 	int	j;
// 	int	nb_dollar;

// 	i = 0;
// 	j = 0;
// 	nb_dollar = 0;
// 	len_final = ft_strlen(str);
// 	len_final -= nb_quotes(str);
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			j = i;
// 			if (str[i] != '?')
// 			{
// 				while (str[i] && (str[i] != '$' && str[i] != ' '
// 						&& str[i] != '\t' && str[i] != '\'' && str[i] != '\"'))
// 					i++;
// 			}
// 			if (tab_dollar[nb_dollar] == 0)
// 				len_final -= i - j + 1;
// 			else if (tab_dollar[nb_dollar] == 2)
// 				len_final += value_size(context, str, i, j) - (i - j + 1);
// 			else if (tab_dollar[nb_dollar] == 3)
// 				len_final += nb_char_interr(context) - 2;
// 			nb_dollar++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (len_final);
// }

// int	compte_taille(t_context *context, char *str)
// {
// 	int	i;
// 	int	nb_dollar;
// 	int	*tab_dollar;
// 	int	len;

// 	i = 0;
// 	nb_dollar = count_dollar(str);
// 	tab_dollar = is_expendable(context, str, nb_dollar);
// 	len = calcul_len(context, tab_dollar, str);
// 	free(tab_dollar);
// 	return (len);
// }

// char	*enleve_quotes(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		quote;
// 	char	*res;

// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	res = malloc(sizeof(char) * (ft_strlen(str) - nb_quotes(str) + 1));
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		while (str[i] && quote == 0)
// 		{
// 			quote = is_quoted(str[i], 0);
// 			if (str[i] && quote == 0)
// 			{
// 				res[j] = str[i];
// 				j++;
// 			}
// 			i++;
// 		}
// 		while (str[i] && quote != 0)
// 		{
// 			quote = is_quoted(str[i], 0);
// 			if (str[i] && quote != 0)
// 			{
// 				res[j] = str[i];
// 				j++;
// 			}
// 			i++;
// 		}
// 	}
// 	is_quoted('a', 1);
// 	res[j] = '\0';
// 	return (res);
// }

// char	*get_value(t_context *context, char *str, int size)
// {
// 	t_elist	*env;

// 	env = context->env;
// 	while (env)
// 	{
// 		if (!ft_strncmp(env->content[0], str, size)
// 			&& size == (int)ft_strlen(env->content[0]))
// 			return (env->content[1]);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// char	*enleve_dollar(t_context *context, char *str, int **tab_dollar,
// 		int taille)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		nb_dollar;
// 	char	*res;
// 	char	*value;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	nb_dollar = 0;
// 	res = malloc(sizeof(char) * (taille + 1));
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			j = -1;
// 			i++;
// 			if (tab_dollar[0][nb_dollar] == 0)
// 			{
// 				// printf("rentre 0\n");
// 				while (++j < tab_dollar[1][nb_dollar])
// 					i++;
// 			}
// 			else if (tab_dollar[0][nb_dollar] == 1)
// 			{
// 				// printf("rentre 1\n");
// 				while (++j < tab_dollar[1][nb_dollar])
// 				{
// 					res[k] = str[i - 1];
// 					i++;
// 					k++;
// 				}
// 				res[k] = str[i - 1];
// 				k++;
// 			}
// 			else if (tab_dollar[0][nb_dollar] == 2)
// 			{
// 				// printf("rentre 2\n");
// 				while (++j < tab_dollar[1][nb_dollar])
// 					i++;
// 				value = get_value(context, str + i - tab_dollar[1][nb_dollar],
// 						tab_dollar[1][nb_dollar]);
// 				ft_strlcpy(res + k, value, ft_strlen(value) + 1);
// 				k += ft_strlen(value);
// 			}
// 			else if (tab_dollar[0][nb_dollar] == 3)
// 			{
// 				value = ft_itoa(context->exit_code);
// 				ft_strlcpy(res + k, value, ft_strlen(value) + 1);
// 				k += ft_strlen(value);
// 				free(value);
// 				i++;
// 			}
// 			nb_dollar++;
// 		}
// 		else
// 		{
// 			res[k] = str[i];
// 			i++;
// 			k++;
// 		}
// 	}
// 	res[k] = '\0';
// 	return (res);
// }

// char	*replace_value(t_context *context, char *str, char *result,
// 		int **tab_dollar)
// {
// 	char	*new_str;
// 	int		taille;

// 	new_str = enleve_quotes(str);
// 	taille = compte_taille(context, str);
// 	result = enleve_dollar(context, new_str, tab_dollar, taille);
// 	free(new_str);
// 	return (result);
// }

// int	nb_interr(char *str)
// {
// 	int	i;
// 	int	res;

// 	i = 0;
// 	res = 0;
// 	while (str[i])
// 	{
// 		if (is_quoted(str[i], 0) != 1 && str[i] == '$')
// 		{
// 			if (str[i + 1] == '?')
// 				res++;
// 		}
// 		i++;
// 	}
// 	is_quoted('z', 1);
// 	return (res);
// }

// char	*replace_interr(t_context *context, char *str)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*result;
// 	char	*ex;

// 	i = 0;
// 	k = i;
// 	ex = ft_itoa(context->exit_code);
// 	if (!ex)
// 		return (NULL);
// 	result = malloc(sizeof(char) * (ft_strlen(str) - (nb_interr(str) * 2)
// 				+ nb_interr(str) * nb_char_interr(context) + 1));
// 	if (!result)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		j = 0;
// 		if (is_quoted(str[i], 0) != 1 && str[i] == '$')
// 		{
// 			if (str[i + 1] == '?')
// 			{
// 				while (ex[j])
// 					result[k++] = ex[j++];
// 				i++;
// 			}
// 			else
// 				result[k++] = str[i];
// 		}
// 		else
// 			result[k++] = str[i];
// 		i++;
// 	}
// 	result[k] = '\0';
// 	is_quoted('g', 1);
// 	free(ex);
// 	return (result);
// }

// char	**expand_total(t_context *context, char *str)
// {
// 	char	*result;
// 	int		**tab_dollar;
// 	char	**splitted;
// 	int		*space_expand;
// 	int		nb_spaces;
// 	int		i;
// 	int		nb_spaces_split;

// 	i = 0;
// 	result = NULL;
// 	tab_dollar = malloc(sizeof(int *) * 2);
// 	tab_dollar[0] = is_expendable(context, str, count_dollar(str));
// 	tab_dollar[1] = size_key(str, count_dollar(str));
// 	space_expand = fill_space_expand(context, str, tab_dollar);
// 	nb_spaces = nb_space(context, str, tab_dollar);
// 	nb_spaces_split = nb_space_split(context, str, tab_dollar);
// 	result = replace_value(context, str, result, tab_dollar);
// 	splitted = split_expand(result, space_expand, nb_spaces_split,
// 			nb_space(context, str, tab_dollar));
// 	free(tab_dollar[0]);
// 	free(tab_dollar[1]);
// 	free(tab_dollar);
// 	free(result);
// 	free(space_expand);
// 	return (splitted);
// }

// void	insert_list(t_list *cmd, char *value)
// {
// 	t_list	*new;

// 	new = ft_lstnew(value);
// 	new->next = cmd->next;
// 	cmd->next = new;
// }

// void	ft_affiche_lst(t_list *lst)
// {
// 	t_list	*temp;

// 	temp = lst;
// 	while (temp)
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp->next;
// 	}
// }

// t_list	*insert_command(t_list *cmd, char **splitted, int *i, int *j)
// {
// 	cmd->next->content = splitted[0];
// 	if (splitted[0])
// 	{
// 		while (splitted[(*i)])
// 			(*i)++;
// 		(*i)--;
// 		(*j) = (*i);
// 		while ((*i) > 0)
// 		{
// 			insert_list(cmd->next, splitted[(*i)]);
// 			(*i)--;
// 		}
// 		while ((*j) > 0)
// 		{
// 			cmd = cmd->next;
// 			(*j)--;
// 		}
// 	}
// 	free(splitted);
// 	cmd = cmd->next;
// 	return (cmd);
// }

// t_list	*insert_first_cmd(t_list *cmd, char **splitted, int *i, int *j)
// {
// 	free(cmd->content);
// 	cmd->content = splitted[0];
// 	if (splitted[0])
// 	{
// 		while (splitted[(*i)])
// 			(*i)++;
// 		(*i)--;
// 		(*j) = (*i);
// 		while ((*i) > 0)
// 		{
// 			insert_list(cmd, splitted[(*i)]);
// 			(*i)--;
// 		}
// 		while ((*j) > 0)
// 		{
// 			cmd = cmd->next;
// 			(*j)--;
// 		}
// 	}
// 	return (cmd);
// }

// void	boucle_expand_cmd(t_list *cmd, t_context *context, int *i, int *j)
// {
// 	t_list	*temp;
// 	char	**splitted;

// 	splitted = NULL;
// 	temp = NULL;
// 	while (cmd && cmd->next)
// 	{
// 		*i = 1;
// 		temp = cmd->next->next;
// 		splitted = expand_total(context, cmd->next->content);
// 		free(cmd->next->content);
// 		if (!splitted)
// 		{
// 			free(cmd->next);
// 			cmd->next = temp;
// 		}
// 		else
// 			cmd = insert_command(cmd, splitted, i, j);
// 	}
// }

// void	free_in_insert(t_list *cmd)
// {
// 	free(cmd->content);
// 	free(cmd);
// }

// void	expand_in_cmd(t_context *context, t_block *block)
// {
// 	t_list	*cmd;
// 	t_list	*temp;
// 	char	**splitted;
// 	int		i[2];

// 	i[1] = 1;
// 	cmd = block->cmd_list;
// 	if (cmd)
// 	{
// 		splitted = expand_total(context, cmd->content);
// 		while (!splitted && cmd)
// 		{
// 			temp = cmd->next;
// 			free_in_insert(cmd);
// 			cmd = temp;
// 			block->cmd_list = cmd;
// 			if (cmd)
// 				splitted = expand_total(context, cmd->content);
// 		}
// 		i[0] = 1;
// 		if (cmd)
// 			cmd = insert_first_cmd(cmd, splitted, &(i[0]), &(i[1]));
// 		free(splitted);
// 		boucle_expand_cmd(cmd, context, &(i[0]), &(i[1]));
// 	}
// }

// // void    expand_in_cmd(t_context *context, t_block *block)
// // {
// //     t_list  *cmd;
// // 	t_list	*temp;
// // 	char	**splitted;
// //     int     i;
// // 	int		j;

// // 	j = 1;
// //     cmd = block->cmd_list;
// // 	if (cmd)
// // 	{
// // 		splitted = expand_total(context, cmd->content);
// // 		while (!splitted && cmd)
// // 		{
// // 			temp = cmd->next;
// // 			free(cmd->content);
// // 			free(cmd);
// // 			cmd = temp;
// // 			block->cmd_list = cmd;
// // 			if (cmd)
// // 				splitted = expand_total(context, cmd->content);
// // 		}
// // 		i = 1;
// // 		if (cmd)
// // 		{
// // 			free(cmd->content);
// // 			cmd->content = splitted[0];
// // 			if (splitted[0])
// // 			{
// // 				while (splitted[i])
// // 					i++;
// // 				i--;
// // 				j = i;
// // 				while (i > 0)
// // 				{
// // 					insert_list(cmd, splitted[i]);
// // 					i--;
// // 				}
// // 				while (j > 0)
// // 				{
// // 					cmd = cmd->next;
// // 					j--;
// // 				}
// // 			}
// // 		}
// // 		free(splitted);
// // 		while (cmd && cmd->next)
// // 		{
// // 			i = 1;
// // 			temp = cmd->next->next;
// // 			splitted = expand_total(context, cmd->next->content);
// // 			free(cmd->next->content);
// // 			if (!splitted)
// // 			{
// // 				free(cmd->next);
// // 				cmd->next = temp;
// // 			}
// // 			else
// // 			{
// // 				cmd->next->content = splitted[0];
// // 				if (splitted[0])
// // 				{
// // 					while (splitted[i])
// // 						i++;
// // 					i--;
// // 					j = i;
// // 					while (i > 0)
// // 					{
// // 						insert_list(cmd->next, splitted[i]);
// // 						i--;
// // 					}
// // 					while (j > 0)
// // 					{
// // 						cmd = cmd->next;
// // 						j--;
// // 					}
// // 				}
// // 				free(splitted);
// // 				cmd = cmd->next;
// // 			}
// // 		}
// // 	}
// // }

// void	expand(t_context *context)
// {
// 	t_block *block;
// 	block = context->block;
// 	while (block)
// 	{
// 		expand_in_cmd(context, block);
// 		expand_in_redir(context, block);
// 		block = block->next;
// 	}
// }