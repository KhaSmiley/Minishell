/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/19 01:25:40 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_token *tok;
	tok = NULL;
	char **envp_cpy;
	char *input;

	envp_cpy = ft_envp_copy(envp);
	while (1)
	{
		input = readline("> ");
		if (!input)
			break;
		if (!*input)
			continue;
		add_history(input);
		if (!manage_quote_errors(input))
		{
			printf("quitting quote error\n");
			free(input);
			continue ;
		}
		tok = find_token(input);
		ft_expand_str(tok, envp_cpy);
		// remove quotes in func below
		fix_quotes_token(tok);
		find_str_to_expand(&tok);
		print_list(tok);
		print_list_env(tok);
		// builtins
		to_builtin_or_not_to_builtin(tok, envp_cpy);
		free(input);
		free_tok(&tok);
	}
	free_tok(&tok);
	free_envp_cpy(envp_cpy);
    return (0);
}
