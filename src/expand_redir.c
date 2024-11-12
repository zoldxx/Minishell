/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:04 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:05 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	boucle_expand_redir(t_redir *redir, t_context *context, t_block *block,
		int *i)
{
	t_redir		*temp;
	t_expand	*expand_redir;

	expand_redir = block->exp_redir;
	temp = NULL;
	while (redir && redir->next)
	{
		i[0] = 1;
		temp = redir->next->next;
		expand_total_redir(context, block, redir->next->filename);
		if (block->fail_malloc == 1 || a(redir, expand_redir->splitted, block))
			return ;
		free(redir->next->filename);
		if (!(expand_redir->splitted))
		{
			free(redir->next);
			redir->next = temp;
		}
		else
		{
			redir = insert_redir(redir, block, &i[0], &i[1]);
			if (block->fail_malloc == 1)
				return ;
		}
	}
}

t_redir	*insert_first_redir(t_redir *redir, t_block *block, int *i, int *j)
{
	free(redir->filename);
	redir->filename = block->exp_redir->splitted[0];
	if (block->exp_redir->splitted[0])
	{
		while (block->exp_redir->splitted[(*i)])
			(*i)++;
		(*i)--;
		(*j) = (*i);
		while ((*i) > 0)
		{
			insert_redir_list(block, redir, block->exp_redir->splitted[(*i)]);
			if (block->fail_malloc == 1)
				return (NULL);
			(*i)--;
		}
		while ((*j) > 0)
		{
			redir = redir->next;
			(*j)--;
		}
	}
	return (redir);
}

void	free_in_insert_redir(t_redir *redir)
{
	if (redir)
	{
		if (redir->filename)
			free(redir->filename);
		free(redir);
	}
}

void	normception(t_context *context, t_block *block, t_redir *redir,
		t_expand *expand_redir)
{
	t_redir	*temp;

	temp = NULL;
	expand_total_redir(context, block, redir->filename);
	if (block->fail_malloc == 1)
		return ;
	while (!expand_redir->splitted && redir)
	{
		boucle_redir(temp, redir, block);
		if (redir)
		{
			expand_total_redir(context, block, redir->filename);
			if (block->fail_malloc == 1)
				return ;
		}
	}
}

void	expand_in_redir(t_context *context, t_block *block)
{
	t_redir		*redir;
	t_expand	*expand_redir;
	int			i[2];

	i[1] = 1;
	expand_redir = block->exp_redir;
	redir = block->redir_list;
	if (redir)
	{
		normception(context, block, redir, expand_redir);
		i[0] = 1;
		if (is_next_ambiguous(redir, expand_redir->splitted, block) == 1)
			return ;
		if (redir)
		{
			redir = insert_first_redir(redir, block, &(i[0]), &(i[1]));
			if (block->fail_malloc == 1)
				return ;
		}
		free(expand_redir->splitted);
		expand_redir->splitted = NULL;
		boucle_expand_redir(redir, context, block, i);
		if (block->fail_malloc == 1)
			return ;
	}
}

// void	expand_in_redir(t_context *context, t_block *block)
// {
// 	t_redir		*redir;
// 	t_redir		*temp;
// 	t_expand	*expand_redir;
// 	int			i[2];

// 	i[1] = 1;
// 	expand_redir = block->exp_redir;
// 	redir = block->redir_list;
// 	temp = NULL;
// 	if (redir)
// 	{
// 		expand_total_redir(context, block, redir->filename);
// 		if (block->fail_malloc == 1)
// 			return ;
// 		while (!expand_redir->splitted && redir)
// 		{
// 			boucle_redir(temp, redir, block);
// 			if (redir)
// 			{
// 				expand_total_redir(context, block, redir->filename);
// 				if (block->fail_malloc == 1)
// 					return ;
// 			}
// 		}
// 		i[0] = 1;
// 		if (is_next_ambiguous(redir, expand_redir->splitted, block) == 1)
// 			return ;
// 		if (redir)
// 		{
// 			redir = insert_first_redir(redir, block, &(i[0]), &(i[1]));
// 			if (block->fail_malloc == 1)
// 				return ;
// 		}
// 		free(expand_redir->splitted);
// 		expand_redir->splitted = NULL;
// 		boucle_expand_redir(redir, context, block, i);
// 		if (block->fail_malloc == 1)
// 			return ;
// 	}
// }

// void	boucle_expand_redir(t_redir *redir, t_context *context,
// 	t_block *block, int *i)
// {
// 	t_redir		*temp;
// 	t_expand	*expand_redir;

// 	expand_redir = block->exp_redir;
// 	temp = NULL;
// 	while (redir && redir->next)
// 	{
// 		i[0] = 1;
// 		temp = redir->next->next;
// 		expand_total_redir(context, block, redir->next->filename);
// 		if (block->fail_malloc == 1)
// 			return ;
// 		if (is_ambiguous(redir, expand_redir->splitted, block))
// 			return ;
// 		free(redir->next->filename);
// 		if (!(expand_redir->splitted))
// 		{
// 			free(redir->next);
// 			redir->next = temp;
// 		}
// 		else
// 		{
// 			redir = insert_redir(redir, block, &i[0], &i[1]);
// 			if (block->fail_malloc == 1)
// 				return ;
// 		}
// 	}
// }

// void	expand_in_redir(t_context *context, t_block *block)
// {
// 	t_redir	*redir;
// 	t_redir	*temp;
// 	char	**splitted;
// 	int		i[2];

// 	i[1] = 1;
// 	redir = block->redir_list;
// 	if (redir)
// 	{
// 		splitted = expand_total(context, redir->filename);
// 		while (!splitted && redir)
// 		{
// 			temp = redir->next;
// 			free_in_insert_redir(redir);
// 			redir = temp;
// 			block->redir_list = redir;
// 			if (redir)
// 				splitted = expand_total(context, redir->filename);
// 		}
// 		i[0] = 1;
// 		if (is_next_ambiguous(redir, splitted, block) == 1)
// 			return ;
// 		if (redir)
// 			redir = insert_first_redir(redir, splitted, &(i[0]), &(i[1]));
// 		free(splitted);
// 		boucle_expand_redir(redir, context, block, i);
// 	}
// }
