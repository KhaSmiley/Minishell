/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/02 00:26:29 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	sig_return;

// handle ctrl C SIGINT with sigaction
void	ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	sig_return = 130;
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &(ctrl_c);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	static t_data	data = {0};
	t_token			*tok;
	char			*input;

	(void)argv;
	tok = NULL;
	ft_envp_copy_export(&data, envp);
	while (1)
	{
		handle_signals();
		input = readline("baznboul> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		if (parsing_and_stock_input(input, &tok, &data))
		{
			printf("ERROR\n");
			free(input);
			continue ;
		}
		init_data(argc, &data, tok);
		if (data.nb_cmd == 1 && (to_builtin_or_not_to_builtin(find_first_cmd(&tok))))
		{
			one_built_in((tok_to_tab(&tok, 0)), tok, &data);
			free_tok(&tok);
			free(input);
			continue ;
		}
		printf("last sig_return: %d\n", sig_return);
		exec_pipe(&data, &tok);
		free(input);
		free_tok(&tok);
	}
	close(data.pipe_fd[0]);
	free_export(data.env_export);
	free_tok(&tok);
	rl_clear_history();
	printf("last sig_return: %d\n", sig_return);
	return (0);
}
