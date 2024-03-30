/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 05:31:16 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/26 04:33:53 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_stock_key_and_value_env(t_token *tok, char *str, int *count, t_export *env)
{
	char	*key;
	char	*value;

	key = ft_find_key(str, (*count));
	value = ft_find_value(key, env);
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

char	*ft_find_value(char *key, t_export *env)
{
	int		i;
	char	*stock;
	t_export *tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			stock = ft_strdup(tmp->value);
			if (!stock)
				return (NULL);
			return (stock);
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

// Trying to create a new env list with the key and value found for each word with $ in it
// so i can use it later to replace the word with the value if necessary (quote handling)

int	ft_create_env(t_token *tok, char *str, t_export *env)
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
				ft_stock_key_and_value_env(tok, str, &count, env);
			}
		}
		i++;
	}
	return (0);
}

// Trying to check for word with $ and expand it,
// the reason i wanna do it before deleting quotes is
// echo test"$USER"test the value to expend is USER but becomes USERTEST without quotes)

void	ft_expand_str(t_token *tok, t_data *data)
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
				ft_create_env(tok, tok->str, data->env_export);
			}
		}
		tok = tok->next;
	}
}
