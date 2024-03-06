/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 05:31:16 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/06 05:31:39 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Trying to find the value with the key
// value is the string after the = in the env list
// ex : USER=kboulkri, key is USER and value is kboulkri


char	*ft_find_value(char *key, char **envp_cpy)
{
	int		i;
	char	*stock;
	i = 0;
	while (envp_cpy[i])
	{
		if (ft_strncmp(envp_cpy[i], key, ft_strlen(key)) == 0)
		{
			if (envp_cpy[i][ft_strlen(key)] == '=')
			{
				stock = ft_substr(envp_cpy[i], ft_strlen_from_char(envp_cpy[i],
							'=') + 1, ft_strlen(envp_cpy[i]) - ft_strlen(key)
						- 1);
				if (!stock)
					return (NULL);
				return (stock);
			}
		}
		i++;
	}
	return (ft_printf("$%s doesn't exist", key), NULL);
}

// Trying to create a new env list with the key and value found for each word with $ in it
// so i can use it later to replace the word with the value if necessary (quote handling)

t_env	*ft_create_env(t_token *tok, char *str, int i, char **envp_cpy)
{
	char	*key;
	char	*value;
	int		count;

    count = 1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			key = ft_find_key(str, count);
            value = ft_find_value(key, envp_cpy);
            ft_stock_env(&tok->env, ft_lstnew_env(key, value));
            count++;
        }
		i++;
	}
	return (tok->env);
}

// Trying to check for word with $ and expand it, 
// the reason i wanna do it before deleting quotes is
// echo test"$USER"test the value to expend is USER but becomes USERTEST without quotes)

void	ft_expand_str(t_token *tok, char **envp_cpy)
{
	int i;

	while (tok)
	{
		i = 0;
		if (tok->type == WORD && tok->str[i] == '$')
		{
			tok->env = ft_create_env(tok, tok->str, i, envp_cpy);
		}
		tok = tok->next;
	}
	// print_list(tok);
	// print_list_env(tok);
}