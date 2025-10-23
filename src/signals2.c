/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhaddadi <jhaddadi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:19:02 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/25 14:19:08 by jhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_sa(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	sa.sa_handler = handler;
	sigaction(sig, &sa, NULL);
}

void	set_signals_parent(void)
{
	set_sa(SIGINT, SIG_IGN, 0);
	set_sa(SIGQUIT, SIG_IGN, 0);
}

void	set_signals_child(void)
{
	set_sa(SIGINT, SIG_DFL, 0);
	set_sa(SIGQUIT, SIG_DFL, 0);
}

void	set_signals_after_child(void)
{
	set_sa(SIGINT, after_child, 0);
	set_sa(SIGQUIT, SIG_IGN, 0);
}

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_last_sig = sig;
		close(STDIN_FILENO);
	}
}

void	set_signals_heredoc_child(void)
{
	set_sa(SIGINT, heredoc_signal_handler, 0);
	set_sa(SIGQUIT, SIG_IGN, 0);
}
