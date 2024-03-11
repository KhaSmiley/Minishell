/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/08 22:51:10 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    (void)argc;
    (void)argv;
    (void)envp;
    t_token *tok;
    char **envp_cpy;

    while (1)
    {
        char *input = readline("> ");
        if (!input)
            break;
        if (!*input)
            continue;
        add_history(input);
        tok = find_token(input);
		// manage quote syntax errors
		manage_quotes(input);
		// $
        envp_cpy = ft_envp_copy(envp);
        ft_expand_str(tok, envp_cpy);
		// remove quotes
		printf("input: %s\n", input);
		remove_quotes(input);
		printf("after remove quotes: %s\n", input);
        //print_list_env(tok);
	}
    return (0);
}
