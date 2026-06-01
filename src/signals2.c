/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:34:44 by toandrad          #+#    #+#             */
/*   Updated: 2026/06/01 13:30:20 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_wait_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	setup_wait_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_wait_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	handle_cont_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
}

int	cont_event_hook(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

void	setup_cont_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_cont_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
