/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:55:28 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/15 22:04:49 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tok_env(t_env *my_env)
{
	t_env	*tmp;

	if (!my_env)
		return ;
	while (my_env)
	{
		tmp = my_env;
		my_env = (my_env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

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
	if (!*tok || !tok)
		return ;
	while (*tok)
	{
		tmp = *tok;
		*tok = (*tok)->next;
		free(tmp->str);
		tmp->str = NULL;
		free_tok_env(tmp->env);
		free(tmp);
		tmp = NULL;
	}
}
