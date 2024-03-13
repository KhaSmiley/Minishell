/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/13 14:47:24 by kboulkri         ###   ########.fr       */
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
    char *input;

    while (1)
    {
        input = readline("> ");
        if (!input)
            break;
        if (!*input)
            continue;
        add_history(input);
        envp_cpy = ft_envp_copy(envp);
		manage_quotes(input);
        tok = find_token(input);
        ft_expand_str(tok, envp_cpy);
		fix_quotes_token(tok);
        find_str_to_expand(&tok);
        print_list(tok);
        print_list_env(tok);
        // free doesn't work if $ doesn't exist
        free_list(&tok);
        free_tab(envp_cpy);
	}
    return (0);
}
