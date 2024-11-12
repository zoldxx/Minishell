/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:23 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:24 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signum;

void	sigzero(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signum = 130;
	}
}

void	sigun(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_signum = 130;
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		g_signum = 131;
	}
}

void	sigdeux(int sig)
{
	if (sig == SIGINT)
	{
		g_signum = 130;
		close(STDIN_FILENO);
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		g_signum = 131;
	}
}

void	signal_cmd(int sig)
{
	if (g_signum == 130)
		g_signum = 0;
	if (g_signum == 0)
		sigzero(sig);
	else if (g_signum == 1)
		sigun(sig);
	else if (g_signum == 2)
		sigdeux(sig);
}

void	reset_signals(t_context *context)
{
	if (g_signum > 2)
	{
		context->exit_code = g_signum;
		g_signum = 0;
	}
}
