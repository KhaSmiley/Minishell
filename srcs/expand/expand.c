/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:12:21 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/10 19:34:44 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_expand_str(t_token *tok, t_data *data)
{
	t_token	*tmp;

	if (!tok)
		return ;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->str, '$'))
		{
			tmp->str = ft_get_new_str_for_env(tmp->str, data);
		}
		tmp = tmp->next;
	}
}

char	*ft_find_value_env_new(char *str, int *i, t_data *data)
{
	char	*key;
	char	*value;
	int		size;
	int		j;

	j = 0;
	size = ft_find_value_malloc(str, i);
	key = malloc(sizeof(char) * (size) + 1);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		key[j] = str[*i];
		(*i)++;
		j++;
	}
	key[j] = '\0';
	value = ft_find_value(key, data->env_export);
	if (!value)
		return (free(key), ft_strdup(""));
	return (free(key), ft_strdup(value));
}

char	*double_quote(char *str, int *i, t_data *data)
{
	char	*env_str;

	env_str = NULL;
	(*i)++;
	env_str = ft_strjoinou(env_str, ft_strdup("\""));
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			env_str = ft_strjoinou(env_str, find_new_str_env(str, i, data));
		else
			env_str = ft_strjoinou(env_str, to_next_double_q(str, i));
		data->status = 0;
	}
	(*i)++;
	return (ft_strjoinou(env_str, ft_strdup("\"")));
}

char	*find_new_str_env(char *str, int *i, t_data *data)
{
	char	*env;
	int		ret;

	(*i)++;
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	if (str[*i] == '?')
	{
		(*i)++;
		ret = choose_return(data);
		return (ft_itoa(ret));
	}
	if ((str[*i] == '\'' || str[*i] == '"') && !is_last(str, *i))
		return (ft_strdup(""));
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	env = ft_find_value_env_new(str, i, data);
	return (env);
}

char	*ft_get_new_str_for_env(char *str, t_data *data)
{
	char	*env_str;
	int		i;

	i = 0;
	env_str = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			env_str = ft_strjoinou(env_str, single_quote(str, &i));
		if (str[i] == '\"')
			env_str = ft_strjoinou(env_str, double_quote(str, &i, data));
		if (str[i] == '$')
		{
			env_str = ft_strjoinou(env_str, find_new_str_env(str, &i,
						data));
			data->status = 0;
		}
		else
			env_str = ft_strjoinou(env_str, normal(str, &i));
	}
	free(str);
	return (env_str);
}
