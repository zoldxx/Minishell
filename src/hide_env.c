/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:33 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:34 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_hide_env(t_elist *copy, t_elist *cheapest, t_elist *start_copy)
{
	t_elist	*temp_free;

	temp_free = NULL;
	while (copy->next != cheapest)
		copy = copy->next;
	if (copy->next->next)
	{
		temp_free = copy->next->next;
		free(copy->next);
		copy->next = temp_free;
		copy = start_copy;
	}
	else
	{
		free(copy->next);
		copy->next = NULL;
		copy = start_copy;
	}
}

void	boucle_hide(t_context *context, t_elist *copy, t_elist *cheapest,
		t_elist *start_copy)
{
	if (copy)
	{
		while (copy->next)
		{
			cheapest = copy;
			while (copy)
			{
				if (ft_strcmp(copy->content[0], cheapest->content[0]) < 0)
					cheapest = copy;
				copy = copy->next;
			}
			ft_elstadd_back(&(context->hide_env),
				ft_elstnew(context, cheapest->content));
			copy = start_copy;
			if (copy == cheapest)
			{
				start_copy = copy->next;
				free(copy);
				copy = start_copy;
			}
			else
				fill_hide_env(copy, cheapest, start_copy);
		}
		tout_pour_la_norm(context, copy);
	}
}

void	init_hide_env(t_context *context)
{
	t_elist	*cheapest;
	t_elist	*copy;
	t_elist	*temp;
	t_elist	*temp_free;
	t_elist	*start_copy;

	copy = NULL;
	start_copy = NULL;
	temp = context->env;
	cheapest = NULL;
	temp_free = NULL;
	while (temp)
	{
		ft_elstadd_back(&copy, ft_elstnew(context, ft_strdup_tab(context,
					temp->content)));
		temp = temp->next;
	}
	temp = context->env;
	start_copy = copy;
	boucle_hide(context, copy, cheapest, start_copy);
}

void	insert_hide_key_utils(t_context *context, t_elist *temp, char *str,
		t_elist *new_maillon)
{
	t_elist	*temp2;

	temp2 = NULL;
	while (temp->next)
	{
		if (ft_strcmp(str, temp->next->content[0]) < 0)
		{
			new_maillon = ft_elstnew(context, split_key_value(context, str));
			temp2 = temp->next;
			temp->next = new_maillon;
			new_maillon->next = temp2;
			return ;
		}
		temp = temp->next;
	}
}

void	insert_hide_key(t_context *context, char *str)
{
	t_elist	*temp;
	t_elist	*temp2;
	t_elist	*new_maillon;

	temp = context->hide_env;
	temp2 = NULL;
	new_maillon = NULL;
	if (temp)
	{
		if (temp->content && ft_strcmp(str, temp->content[0]) < 0)
		{
			ft_elstadd_front(&(context->hide_env),
				ft_elstnew(context, split_key_value(context, str)));
			return ;
		}
		insert_hide_key_utils(context, temp, str, new_maillon);
	}
	ft_elstadd_back(&(context->hide_env), ft_elstnew(context,
			split_key_value(context, str)));
}

// void	insert_hide_key(t_context *context, char *str)
// {
// 	t_elist	*temp;
// 	t_elist	*temp2;
// 	t_elist	*new_maillon;

// 	temp = context->hide_env;
// 	if (temp)
// 	{
// 		if (temp->content && ft_strcmp(str, temp->content[0]) < 0)
// 		{
// 			ft_elstadd_front(&(context->hide_env),
// 				ft_elstnew(split_key_value(str)));
// 			return ;
// 		}
// 		while (temp->next)
// 		{
// 			if (ft_strcmp(str, temp->next->content[0]) < 0)
// 			{
// 				new_maillon = ft_elstnew(split_key_value(str));
// 				temp2 = temp->next;
// 				temp->next = new_maillon;
// 				new_maillon->next = temp2;
// 				return ;
// 			}
// 			temp = temp->next;
// 		}
// 	}
// 	ft_elstadd_back(&(context->hide_env), ft_elstnew(split_key_value(str)));
// }

// void	init_hide_env(t_context *context)
// {
// 	t_elist	*cheapest;
// 	t_elist	*copy;
// 	t_elist	*temp;
// 	t_elist	*temp_free;
// 	t_elist	*start_copy;

// 	copy = NULL;
// 	start_copy = NULL;
// 	temp = context->env;
// 	cheapest = NULL;
// 	while (temp)
// 	{
// 		ft_elstadd_back(&copy, ft_elstnew(ft_strdup_tab(temp->content)));
// 		temp = temp->next;
// 	}
// 	temp = context->env;
// 	start_copy = copy;
// 	if (copy)
// 	{
// 		while (copy->next)
// 		{
// 			cheapest = copy;
// 			while (copy)
// 			{
// 				if (ft_strcmp(copy->content[0], cheapest->content[0]) < 0)
// 					cheapest = copy;
// 				copy = copy->next;
// 			}
// 			ft_elstadd_back(&(context->hide_env),
// 				ft_elstnew(cheapest->content));
// 			copy = start_copy;
// 			if (copy == cheapest)
// 			{
// 				start_copy = copy->next;
// 				free(copy);
// 				copy = start_copy;
// 			}
// 			else
// 			{
// 				while (copy->next != cheapest)
// 					copy = copy->next;
// 				if (copy->next->next)
// 				{
// 					temp_free = copy->next->next;
// 					free(copy->next);
// 					copy->next = temp_free;
// 					copy = start_copy;
// 				}
// 				else
// 				{
// 					free(copy->next);
// 					copy->next = NULL;
// 					copy = start_copy;
// 				}
// 			}
// 		}
// 		ft_elstadd_back(&(context->hide_env), ft_elstnew(copy->content));
// 		free(copy);
// 	}
// }

// void	init_hide_env(t_context *context)
// {
// 	t_elist	*cheapest;
// 	t_elist	*copy;
// 	t_elist	*temp;
// 	t_elist	*temp_free;
// 	t_elist	*start_copy;

// 	copy = NULL;
// 	start_copy = NULL;
// 	temp = context->env;
// 	cheapest = NULL;
// 	while (temp)
// 	{
// 		ft_elstadd_back(&copy, ft_elstnew(ft_strdup_tab(temp->content)));
// 		temp = temp->next;
// 	}
// 	temp = context->env;
// 	start_copy = copy;
// 	while (copy->next)
// 	{
// 		cheapest = copy;
// 		// printf("DEBUT   copy content = %s\n", copy->content[0]);
// 		// printf("copy next content = %s\n", copy->next->content[0]);
// 		while (copy->next)
// 		{
// 			if (ft_strcmp(copy->content[0], cheapest->content[0]) < 0)
// 			{
// 				cheapest = copy;
// 			}
// 			copy = copy->next;
// 		}
// 		ft_elstadd_back(&(context->hide_env), ft_elstnew(cheapest->content));
// 		copy = start_copy;
// 		if (copy == cheapest)
// 		{
// 			start_copy = copy->next;
// 			// free(copy->content[0]);
// 			// free(copy->content[1]);
// 			// free(copy->content);
// 			free(copy);
// 			copy = start_copy;
// 		}
// 		else
// 		{
// 			while (copy->next != cheapest)
// 				copy = copy->next;
// 			if (copy->next->next)
// 			{
// 				temp_free = copy->next->next;
// 				// free(copy->next->content[0]);
// 				// free(copy->next->content[1]);
// 				// free(copy->next->content);
//				free(copy->next);
// 				copy->next = temp_free;
// 				copy = start_copy;
// 			}
// 			else
// 			{
// 				// free(copy->next->content[0]);
// 				// free(copy->next->content[1]);
// 				// free(copy->next->content);
// 				free(copy->next);
// 				copy->next = NULL;
// 				copy = start_copy;
// 			}
// 		}
// 	}
// 		printf("copy content = %s\n", copy->content[0]);
// 		ft_elstadd_back(&(context->hide_env), ft_elstnew(copy->content));
// 		// free(copy->content[0]);
// 		// free(copy->content[1]);
// 		// free(copy->content);
// 		free(copy);
// 	// printf("FIN    copy content = %s\n", copy->content[0]);
// 	// printf("copy next content = %s\n", copy->next->content[0]);
// }
