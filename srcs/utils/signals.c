/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:38:15 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/11 15:03:53 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	sigint_hd(int signum)
{
	t_data	*data;
	int		i;

	i = -1;
	(void)signum;
	data = simpleton();
	write(1, "\n", 1);
	while (++i < data->nb_hd)
	{
		close(data->here_docs[i].fd[1]);
		close(data->here_docs[i].fd[0]);
	}
	if (data->flag_hd == 1)
	{
		dup2(data->std_fd[0], STDIN_FILENO);
		dup2(data->std_fd[1], STDOUT_FILENO);
		close(data->std_fd[0]);
		close(data->std_fd[1]);
		free_tab(data->builtin);
	}
	free_export(data->env_export);
	free_tok(&data->tok);
	free(data->here_docs);
	exit(130);
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &(sigint_handler);
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	disable_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
