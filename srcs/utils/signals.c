/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:38:15 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/05 18:05:48 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	//printf("signum = %d\n", signum);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (!g_sig_return)
		g_sig_return = 130;
	else
		g_sig_return = 0;
}

void	sigint_hd(int signum)
{
	(void)signum;
	// data = simpleton();
	// ft_printf("quitting hd ctrl c\n");
	write(1, "\n", 1);
	// use data to free/ close everything
	exit(130);
}
void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &(sigint_handler);
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
