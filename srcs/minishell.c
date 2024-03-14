/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/14 17:10:46 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_all(char *input, t_token **tok, char **envp_cpy)
{
	if (input)
		free(input);
	if (*tok && tok)
		free_list(tok);
	if (*envp_cpy && envp_cpy)
		free_tab(envp_cpy);
	return (0);
}
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_token *tok;
    char **envp_cpy;
    char *input;

	envp_cpy = NULL;
	tok = NULL;
	input = NULL;
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
			free_all(input, &tok, envp_cpy);
			printf("quitting quote error\n");
			return (1);
		}
		tok = find_token(input);
        ft_expand_str(tok, envp_cpy);
		// remove quotes in func below
		fix_quotes_token(tok);
        find_str_to_expand(&tok);
        print_list(tok);
        print_list_env(tok);
		free_list(&tok);
		free(input);
	}
	free_all(input, &tok, envp_cpy);
    return (0);
}
