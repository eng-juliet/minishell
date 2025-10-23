/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:05:22 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/28 19:13:41 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_sig = 0;

void	signal_reset_prompt(int signo)
{
	(void)signo;
	g_last_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	set_sa(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	sa.sa_handler = handler;
	sigaction(sig, &sa, NULL);
}

void	set_signals_interactive(void)
{
	set_sa(SIGINT, signal_reset_prompt, 0);
	set_sa(SIGQUIT, SIG_IGN, 0);
}

void	after_child(int signo)
{
	if (signo == SIGINT)
		g_last_sig = signo;
}
