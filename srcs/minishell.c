/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/31 06:28:23 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing_and_stock_input(char *input, t_token **tok, t_data *data)
{
	t_token	*tmp;

	tmp = *tok;
	if (!manage_quote_errors(input))
	{
		printf("quitting quote error\n");
		return (1);
	}
	tmp = find_token(input);
    if (ft_syntax(&tmp))
		return (1);
	ft_expand_str(tmp, data);
	fix_quotes_token(tmp);
	find_str_to_expand(&tmp);
	*tok = tmp;
	return (0);
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
		input = readline("> ");
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
			one_built_in((tok_to_tab(&tok, 0)), &data);
			free_tok(&tok);
			free(input);
			continue ;
		}
		exec_pipe(&data, &tok);
		free(input);
		free_tok(&tok);
	}
	close(data.pipe_fd[0]);
	free_export(data.env_export);
	free_tok(&tok);
	return (0);
}
