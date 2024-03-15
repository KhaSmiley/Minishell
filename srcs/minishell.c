/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/15 01:33:26 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_envp_cpy(char **envp_cpy)
{
	int	i;

	i = 0;
	if (!envp_cpy)
		return ;
	while (envp_cpy[i])
	{
		free(envp_cpy[i]);
		i++;
	}
	free(envp_cpy);
}

void	free_tok(t_token **tok)
{
	t_token	*tmp;
	if (!*tok)
		return ;
	while (*tok)
	{
		tmp = *tok;
		*tok = (*tok)->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_tok_env(t_token **tok)
{
	t_token	*tmp;

	if (!*tok)
		return ;
	while (*tok)
	{
		tmp = *tok;
		*tok = (*tok)->next;
		free(tmp->env->key);
		free(tmp->env->value);
		free(tmp->env);
		free(tmp);
	}
}

// free tok and envp_cpy is successful no leaks
// leaks when use funcs to manage expand
// don't free tok->env correctly yet

int main(int argc, char **argv, char **envp)
{
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
		if (!manage_quote_errors(input))
		{
			// free
			printf("quitting quote error\n");
			free(input);
			return (1);
		}
        envp_cpy = ft_envp_copy(envp);
		tok = find_token(input);
       	// ft_expand_str(tok, envp_cpy);
		// remove quotes in func below
		fix_quotes_token(tok);
        //find_str_to_expand(&tok);
        print_list(tok);
        //print_list_env(tok);
		free(input);
		free_tok(&tok);
		//free_tok_env(&tok);
		free_envp_cpy(envp_cpy);
	}
    return (0);
}
