/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:51:51 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:51:52 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_signum;

int	error_args(int ac, char **av)
{
	(void)ac;
	(void)av;
	return (126);
}

void	ctrl_d(t_context *context)
{
	if (context->input_line == NULL)
	{
		ft_free_loop(context);
		ft_free_garbage(context, 0);
		ft_free_all(context);
		printf("exit\n");
		exit(127);
	}
}

void	launch_loop(t_context *context)
{
	add_history(context->input_line);
	if (decoupage(context))
	{
		launch_exec(context);
		ft_free_loop(context);
	}
	else
	{
		if (context->input_line)
		{
			free(context->input_line);
			context->input_line = NULL;
		}
	}
}

void	init_launch(t_context *context)
{
	g_signum = 0;
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	ft_init_loop(context);
}

int	main(int ac, char **av, char **envp)
{
	t_context	context;
	int			exit_code;

	if (ac == 1)
	{
		exit_code = 0;
		(void)av;
		init(&context, envp);
		while (1)
		{
			init_launch(&context);
			context.input_line = readline("MINISHELL : ");
			reset_signals(&context);
			ctrl_d(&context);
			if (context.input_line[0] != 0)
				launch_loop(&context);
			reset_signals(&context);
		}
	}
	else
		return (error_args(ac, av));
	return (0);
}
