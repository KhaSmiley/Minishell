/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/09 09:10:40 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig_return ;

int	empty_str(char *str)
{
	int	i;

	i = 0;
	while (str && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (free(str), 1);
	return (0);
}

void	end_while_main(t_data *data, char *input, t_token **tok)
{
	exec_pipe(data, &data->tok);
	handle_signals();
	free(input);
	free_tok(tok);
	close(data->pipe_fd[0]);
	data->minishell_line_no++;
}

void	main_while(t_data *data, t_token **tok, char *input, int argc)
{
	while (1)
	{
		input = readline("baznboul> ");
		if (input == NULL)
		{
			printf("exit\n");
			data->status = 0;
			break ;
		}
		if (!*input)
			continue ;
		add_history(input);
		if (empty_str(input))
			continue ;
		if (parsing_and_stock_input(input, tok, data))
			continue ;
		init_data(argc, data, data->tok);
		if (data->nb_cmd == 1
			&& (to_builtin_or_not_to_builtin(find_first_cmd(&data->tok))))
		{
			one_built_in((tok_to_tab(&data->tok, 0, data)), &data->tok, data);
			continue ;
		}
		end_while_main(data, input, &data->tok);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_token	*tok;
	char	*input;

	(void)argv;
	(void)argc;
	tok = NULL;
	input = NULL;
	if (!isatty(0))
		return (1);
	data = simpleton();
	handle_signals();
	g_sig_return = 0;
	ft_envp_copy_export(data, envp);
	data->minishell_line_no = 1;
	main_while(data, &tok, input, argc);
	free_export(data->env_export);
	free_tok(&data->tok);
	rl_clear_history();
	return (data->status);
}
