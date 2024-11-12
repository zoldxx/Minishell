/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:05 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:06 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addback_redir(t_block *block, int i, int k, int redir_type)
{
	char	*str;

	str = malloc(sizeof(char) * (i - k + 1));
	if (!str)
		return ;
	if (block->block_line[i])
		ft_strlcpy(str, block->block_line + k, (i - k + 1));
	else
		ft_strlcpy(str, block->block_line + k, (i - k + 1));
	ft_lstadd_backredir(&block->redir_list,
		ft_lstnewredir(block->context, str, redir_type));
}

void	ft_addback_cmd(t_context *context, t_block *block, int i, int k)
{
	char	*str;

	str = malloc(sizeof(char) * (i - k + 1));
	if (!str)
		return ;
	if (block->block_line[i])
		ft_strlcpy(str, block->block_line + k, (i - k + 1));
	else
		ft_strlcpy(str, block->block_line + k, (i - k + 1));
	ft_lstadd_back(&block->cmd_list, fm(context, str));
}

int	is_redir(char c, char d)
{
	if (c == '>' && d != '>')
		return (2);
	else if (c == '>' && d == '>')
		return (4);
	else if (c == '<' && d != '<')
		return (1);
	else if (c == '<' && d == '<')
		return (3);
	return (0);
}

void	ft_nb_command(t_context *context)
{
	t_block	*block;
	int		i;

	i = 1;
	block = context->block;
	while (block)
	{
		block->cmd_number = i;
		i++;
		block = block->next;
	}
}

int	end_parsing(t_context *context)
{
	is_quoted('o', 1);
	if (ft_open_heredocs(context) == 1)
		return (1);
	if (expand(context) == 1)
		ft_free_fail_expand(context);
	ft_nb_command(context);
	create_args(context);
	return (0);
}
