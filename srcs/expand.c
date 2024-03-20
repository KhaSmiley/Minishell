/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 05:31:16 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/19 21:15:37 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_stock_key_and_value_env(t_token *tok, char *str, int *count, char **envp_cpy)
{
	char	*key;
	char	*value;

	key = ft_find_key(str, (*count));
	value = ft_find_value(key, envp_cpy);
	ft_stock_env(&tok->env, ft_lstnew_env(key, value));
	if (!tok->env)
		return (1);
	(*count)++;
	return (0);
}

// Trying to find the value with the key
// value is the string after the = in the env list
// ex : USER=kboulkri, key is USER and value is kboulkri

void	check_quotes_for_env(char *quote_char, char *word, int i_word)
{
	if (!*quote_char)
		*quote_char = word[i_word];
	else if (*quote_char == word[i_word])
		*quote_char = '\0';
}

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
	return (ft_strdup(""));
}

// Trying to create a new env list with the key and value found for each word with $ in it
// so i can use it later to replace the word with the value if necessary (quote handling)

int	ft_create_env(t_token *tok, char *str, char **envp_cpy)
{
	int		count;
	char	flag_quote;
	int		i;

	i = 0;
	count = 1;
	flag_quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			check_quotes_for_env(&flag_quote, str, i);
		else if (str[i] == '$')
		{
			if (flag_quote == '\'')
				ft_stock_env(&tok->env, ft_lstnew_env(NULL, NULL));
			else
			{
				ft_stock_key_and_value_env(tok, str, &count, envp_cpy);
			}
		}
		i++;
	}
	return (0);
}

// Trying to check for word with $ and expand it,
// the reason i wanna do it before deleting quotes is
// echo test"$USER"test the value to expend is USER but becomes USERTEST without quotes)

void	ft_expand_str(t_token *tok, char **envp_cpy)
{
	if (!tok)
		return ;
	while (tok)
	{
		tok->env = NULL;
		if (tok->type == WORD)
		{
			if (ft_strchr(tok->str, '$'))
			{
				ft_create_env(tok, tok->str, envp_cpy);
			}
		}
		tok = tok->next;
	}
}
