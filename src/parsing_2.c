/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:03 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:04 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_is_quoted(char c, int *single, int *double_q)
{
	if (c == '\'')
	{
		if (*single == 0 && *double_q == 0)
			*single = 1;
		else if (*single == 1 && *double_q == 0)
			*single = 0;
		else if (*single == 0 && *double_q == 1)
			*single = 0;
	}
	else if (c == '"')
	{
		if (*single == 0 && *double_q == 0)
			*double_q = 1;
		else if (*single == 0 && *double_q == 1)
			*double_q = 0;
		else if (*single == 1 && *double_q == 0)
			*double_q = 0;
	}
}

int	is_quoted(char c, int reset)
{
	static int	single = 0;
	static int	double_q = 0;

	if_is_quoted(c, &single, &double_q);
	if (reset == 1)
	{
		single = 0;
		double_q = 0;
	}
	if (single == 0 && double_q == 0)
		return (0);
	else if (single == 1 && double_q == 0)
		return (1);
	else if (single == 0 && double_q == 1)
		return (2);
	else
		return (3);
}

// int	is_quoted(char c, int reset)
// {
// 	static int	single = 0;
// 	static int	double_q = 0;

// 	if (c == '\'')
// 	{
// 		if (single == 0 && double_q == 0)
// 			single = 1;
// 		else if (single == 1 && double_q == 0)
// 			single = 0;
// 		else if (single == 0 && double_q == 1)
// 			single = 0;
// 	}
// 	else if (c == '"')
// 	{
// 		if (single == 0 && double_q == 0)
// 			double_q = 1;
// 		else if (single == 0 && double_q == 1)
// 			double_q = 0;
// 		else if (single == 1 && double_q == 0)
// 			double_q = 0;
// 	}
// 	if (reset == 1)
// 	{
// 		single = 0;
// 		double_q = 0;
// 	}
// 	if (single == 0 && double_q == 0)
// 		return (0);
// 	else if (single == 1 && double_q == 0)
// 		return (1);
// 	else if (single == 0 && double_q == 1)
// 		return (2);
// 	else
// 		return (3);
// }

void	create_args(t_context *context)
{
	t_block	*block;
	t_list	*temp;
	int		i;

	block = context->block;
	while (block)
	{
		i = 0;
		block->cmd_args = ft_malloc_double(context, (ft_lstsize(block->cmd_list)
					+ 1));
		temp = block->cmd_list;
		while (temp)
		{
			block->cmd_args[i] = temp->content;
			temp = temp->next;
			i++;
		}
		block->cmd_args[i] = NULL;
		block = block->next;
	}
}

void	decoupage_utils(t_context *context, int *i)
{
	while (context->input_line[*i])
	{
		if ((is_quoted(context->input_line[*i], 0) == 0)
			&& context->input_line[*i] == '|')
		{
			*i += 1;
			break ;
		}
		*i += 1;
	}
}

int	decoupage(t_context *context)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	if (!ced(context))
		return (0);
	while (context->input_line[i])
	{
		k = i;
		decoupage_utils(context, &i);
		str = ft_malloc(context, i - k + 1);
		if (context->input_line[i])
			ft_strlcpy(str, context->input_line + k, (i - k));
		else
			ft_strlcpy(str, context->input_line + k, (i - k + 1));
		ft_lstadd_backblock(&context->block, ft_lstnewblock(context, str));
		context->nb_command++;
	}
	is_quoted(context->input_line[i], 1);
	if (!end_d(context))
		return (0);
	return (1);
}
