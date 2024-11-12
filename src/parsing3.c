/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:18 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:19 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	init_values_parsing(int *i, int *j, int *quote, int *redir_type)
// {
// 	*quote = 0;
// 	*redir_type = 0;
// 	*i = 0;
// 	*j = *i;
// }

int	init_values_parsing(int *i, int *j, int *quote, int *redir_type)
{
	*quote = 0;
	*redir_type = 0;
	*i = 0;
	*j = *i;
	return (1);
}

void	cmd_or_redir(t_block *block, int *i, int *j, int *redir_type)
{
	if (*i > 0 && block->block_line[*i] == '\0' && block->block_line[*i
			- 1] != ' ')
	{
		if (*redir_type == 0)
			ft_addback_cmd(block->context, block, *i, *j);
		else
			ft_addback_redir(block, *i, *j, *redir_type);
	}
}

void	char_is_a_chevron(t_block *block, int *i, int *j, int *redir_type)
{
	if (*i > 1 && !(block->block_line[*i - 1] == ' '
			|| block->block_line[*i - 1] == '\t'))
	{
		if (*redir_type == 0)
			ft_addback_cmd(block->context, block, *i, *j);
		else
			ft_addback_redir(block, *i, *j, *redir_type);
	}
	*redir_type = is_redir(block->block_line[*i], block->block_line[*i
			+ 1]);
	if (*redir_type == 1 || *redir_type == 2)
	{
		(*i)++;
		*j = *i;
	}
	else if (*redir_type == 3 || *redir_type == 4)
	{
		*i += 2;
		*j = *i;
	}
}

int	word_is_created(t_block *block, int *i, int *j, int *redir_type)
{
	if (block->block_line[*i] == ' ' || block->block_line[*i] == '\t')
	{
		if (*redir_type == 0)
			ft_addback_cmd(block->context, block, *i, *j);
		else
			ft_addback_redir(block, *i, *j, *redir_type);
		(*i)++;
		*j = *i;
		*redir_type = 0;
		return (1);
	}
	else if (block->block_line[*i] == '>' || block->block_line[*i] == '<')
	{
		char_is_a_chevron(block, i, j, redir_type);
		return (1);
	}
	return (0);
}

int	separe_args_redir(t_context *context)
{
	int		i;
	int		j;
	t_block	*block;
	int		redir_type;
	int		quote;

	block = context->block;
	while (block && init_values_parsing(&i, &j, &quote, &redir_type))
	{
		while (block->block_line[i] && mf(context, block, &i, &j))
		{
			quote = is_quoted(block->block_line[i], 0);
			if (quote == 0 && word_is_created(block, &i, &j, &redir_type))
				context->is_created = 1;
			else if (block->block_line[i] == '\0')
				break ;
			else
				i++;
		}
		cmd_or_redir(block, &i, &j, &redir_type);
		block = block->next;
	}
	if (end_parsing(context) == 1)
		return (1);
	return (0);
}

// int	separe_args_redir(t_context *context)
// {
// 	int		i;
// 	int		j;
// 	t_block	*block;
// 	int		redir_type;
// 	int		quote;
// 	block = context->block;
// 	while (block)
// 	{
// 		init_values_parsing(&i, &j, &quote, &redir_type);
// 		while (block->block_line[i])
// 		{
// 			move_forward_in_block_line(context, block, &i, &j);
// 			quote = is_quoted(block->block_line[i], 0);
// 			if (quote == 0 && word_is_created(block, &i, &j, &redir_type))
// 				context->is_created = 1;
// 			else if (block->block_line[i] == '\0')
// 				break ;
// 			else
// 				i++;
// 		}
// 		cmd_or_redir(block, &i, &j, &redir_type);
// 		block = block->next;
// 	}
// 	if (end_parsing(context) == 1)
// 		return (1);
// 	return (0);
// }

// void	separe_args_redir(t_context *context)
// {
// 	int		i;
// 	int		j;
// 	t_block	*block;
// 	int		redir_type;
// 	int		quote;

// 	block = context->block;
// 	while (block)
// 	{
// 		init_values_parsing(&i, &j, &quote, &redir_type);
// 		while (block->block_line[i])
// 		{
// 			move_forward_in_block_line(context, block, &i, &j);
// 			quote = is_quoted(block->block_line[i], 0);
// 			if (quote == 0 && (block->block_line[i] == ' '
// 					|| block->block_line[i] == '\t'))
// 			{
// 				if (redir_type == 0)
// 					ft_addback_cmd(block, i, j);
// 				else
// 					ft_addback_redir(block, i, j, redir_type);
// 				context->is_created = 1;
// 				i++;
// 				j = i;
// 				redir_type = 0;
// 			}
// 			else if (quote == 0 && (block->block_line[i] == '>'
// 					|| block->block_line[i] == '<'))
// 			{
// 				if (i > 1 && !(block->block_line[i - 1] == ' '
// 						|| block->block_line[i - 1] == '\t'))
// 				{
// 					if (redir_type == 0)
// 						ft_addback_cmd(block, i, j);
// 					else
// 						ft_addback_redir(block, i, j, redir_type);
// 				}
// 				redir_type = is_redir(block->block_line[i], block->block_line[i
// 						+ 1]);
// 				if (redir_type == 1 || redir_type == 2)
// 				{
// 					i++;
// 					j = i;
// 				}
// 				else if (redir_type == 3 || redir_type == 4)
// 				{
// 					i += 2;
// 					j = i;
// 				}
// 				context->is_created = 1;
// 			}
// 			else if (quote != 0)
// 				i++;
// 			else if (block->block_line[i] == '\0')
// 				break ;
// 			else
// 				i++;
// 		}
// 		cmd_or_redir(block, &i, &j, &redir_type);
// 		block = block->next;
// 	}
// 	end_parsing(context);
// }

// int	separe_args_redir(t_context *context)
// {
// 	int		i;
// 	int		j;
// 	t_block	*block;
// 	int		redir_type;
// 	int		quote;
// 	int		is_created;

// 	block = context->block;
// 	while (block)
// 	{
// 		quote = 0;
// 		redir_type = 0;
// 		is_created = 1;
// 		i = 0;
// 		j = i;
// 		while (block->block_line[i])
// 		{
// 			while (is_created == 1 && block->block_line[i]
// 				&& (block->block_line[i] == ' '
// 					|| block->block_line[i] == '\t'))
// 			{
// 				i++;
// 				j = i;
// 			}
// 			is_created = 0;
// 			while (block->block_line[i] && is_quoted(block->block_line[i], 0))
// 				i++;
// 			if (block->block_line[i] == '\'' || block->block_line[i] == '\"')
// 				i++;
// 			quote = is_quoted(block->block_line[i], 0);
// 			if (quote == 0 && (block->block_line[i] == ' '
// 					|| block->block_line[i] == '\t'))
// 			{
// 				if (redir_type == 0)
// 					ft_addback_cmd(block, i, j);
// 				else
// 					ft_addback_redir(block, i, j, redir_type);
// 				is_created = 1;
// 				i++;
// 				j = i;
// 				redir_type = 0;
// 			}
// 			else if (quote == 0 && (block->block_line[i] == '>'
// 						|| block->block_line[i] == '<'))
// 			{
// 				if (i > 1 && !(block->block_line[i - 1] == ' '
// 						|| block->block_line[i - 1] == '\t'))
// 				{
// 					if (redir_type == 0)
// 						ft_addback_cmd(block, i, j);
// 					else
// 						ft_addback_redir(block, i, j, redir_type);
// 				}
// 				redir_type = is_redir(block->block_line[i], block->block_line[i
// 						+ 1]);
// 				if (redir_type == 1 || redir_type == 2)
// 				{
// 					i++;
// 					j = i;
// 				}
// 				else if (redir_type == 3 || redir_type == 4)
// 				{
// 					i += 2;
// 					j = i;
// 				}
// 				is_created = 1;
// 			}
// 			else if (quote != 0)
// 				i++;
// 			else if (block->block_line[i] == '\0')
// 				break ;
// 			else
// 				i++;
// 		}
// 		if (i > 0 && block->block_line[i] == '\0' && block->block_line[i
// 			- 1] != ' ')
// 		{
// 			if (redir_type == 0)
// 				ft_addback_cmd(block, i, j);
// 			else
// 				ft_addback_redir(block, i, j, redir_type);
// 		}
// 		block = block->next;
// 	}
// 	is_quoted('o', 1);
// 	// ft_affiche_block_content(context);
// 	ft_open_heredocs(context);
// 	expand(context);
// 	ft_nb_command(context);
// 	create_args(context);
// 	return  (0);
// }
