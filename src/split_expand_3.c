/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:37 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:38 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ise(t_block *block, t_expand *expand, int tot_spaces)
{
	expand = block->expand;
	if (!(expand->result[0]))
	{
		expand->splitted = NULL;
		return (0);
	}
	expand->splitted = malloc(sizeof(char *) * (tot_spaces + 1));
	if (!expand->splitted)
	{
		block->fail_malloc = 1;
		return (0);
	}
	return (1);
}

int	ise_r(t_block *block, t_expand *expand, int tot_spaces)
{
	expand = block->exp_redir;
	if (!(expand->result[0]))
	{
		expand->splitted = NULL;
		return (0);
	}
	expand->splitted = malloc(sizeof(char *) * (tot_spaces + 1));
	if (!expand->splitted)
	{
		block->fail_malloc = 1;
		return (0);
	}
	return (1);
}
