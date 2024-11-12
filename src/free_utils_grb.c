/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_grb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:19 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:20 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_garbage_content(t_context *context)
{
	t_garbage	*tmp;

	tmp = context->garbage;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		if (tmp->tab_str)
			free(tmp->tab_str);
		if (tmp->tab)
			free(tmp->tab);
		if (tmp->big_tab)
			free(tmp->big_tab);
		tmp->str = NULL;
		tmp->tab_str = NULL;
		tmp->tab = NULL;
		tmp->big_tab = NULL;
		tmp = tmp->next;
	}
}

void	ft_free_garbage(t_context *context, int fmal)
{
	t_garbage	*tmp;
	t_garbage	*garbage;

	if (fmal == 1 && context->garbage)
		ft_free_garbage_content(context);
	tmp = context->garbage;
	while (tmp)
	{
		garbage = tmp->next;
		free(tmp);
		tmp = garbage;
	}
	context->garbage = NULL;
	if (fmal == 1 || fmal == 2)
	{
		ft_free_loop(context);
		ft_free_all(context);
		ft_putstr_fd("MALLOC FAIL : FORCE QUIT\n", 2);
		exit (1);
	}
}
