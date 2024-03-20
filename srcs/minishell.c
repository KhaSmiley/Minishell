/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/20 11:49:55 by kboulkri         ###   ########.fr       */
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
	ft_expand_str(tmp, data->envp_cpy);
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
	data.envp_cpy = ft_envp_copy(envp);
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
			free(input);
			continue ;
		}
		init_data(argc, &data, tok);
		exec_pipe(&data, &tok);
		free(input);
		free_tok(&tok);
	}
	close(data.pipe_fd[0]);
	free_tok(&tok);
	free_envp_cpy(data.envp_cpy);
	return (0);
}
