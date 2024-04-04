/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:38:15 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/04 17:03:42 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// handle ctrl C SIGINT with sigaction
void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (!g_sig_return)
		g_sig_return = 130;
	else
		g_sig_return = 0;
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &(sigint_handler);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
