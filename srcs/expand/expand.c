/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:12:21 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/04 16:53:37 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_expand_str_y(t_token *tok, t_data *data)
{
    t_token *tmp;

	if (!tok)
		return ;
    tmp = tok;
    while (tmp)
	{
		if (tmp->type == WORD)
		{
			tmp->str = ft_get_new_str_for_env_y(tmp->str, data);
		}
		tmp = tmp->next;
	}
}
char	*to_next_double_q(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char *ft_find_value_env_new(char *str, int *i, t_data *data)
{
    char *key;
    char *value;
    int start;
    int j;

    j = 0;
    start = *i;
    key = malloc(sizeof (char) * 100);
    while(ft_isalnum(str[*i]) || str[*i] == '_')
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

char *double_quote(char *str, int *i, t_data *data)
{
    char	*env_str;

	env_str = NULL;
	(*i)++;
    env_str = ft_strjoin_you(env_str, ft_strdup("\""));
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			env_str = ft_strjoin_you(env_str, find_new_str_env_y(str, i, data));
		else
			env_str = ft_strjoin_you(env_str, to_next_double_q(str, i));
		data->status = 0;
	}
	(*i)++;
	return (ft_strjoin_you(env_str, ft_strdup("\"")));
}

char *single_quote(char *str, int *i)
{
    int start;

    start = *i;
    (*i)++;
    while (str[*i] != '\'')
        (*i)++;
    (*i)++;
    return (ft_substr(str, start, *i - start));
}

int ft_strl(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (i);
    while(str[i])
        i++;
    return (i);
}

char *ft_strjoin_you(char *s1, char *s2)
{
	int		i;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	res = malloc(ft_strl(s1) + ft_strl(s2) + 1);
	if (!res)
		return (NULL);
	while (i < ft_strl(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (i < ft_strl(s1) + ft_strl(s2))
	{
		res[i] = s2[i - ft_strl(s1)];
		i++;
	}
	res[i] = 0;
	free(s1);
    free(s2);
	return (res);
}


int	is_last(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count % 2);
}

char *find_new_str_env_y(char *str, int *i, t_data *data)
{
    (*i)++;
    if (ft_isdigit(str[*i]))
    {
        (*i)++;
        return (ft_strdup(""));
    }
    if (str[*i] == '?')
    {
        (*i)++;
		if (g_sig_return)
			return (ft_itoa(g_sig_return));
		return (ft_itoa(data->status));
    }
    if ((str[*i] == '\'' || str[*i] == '"') && !is_last(str, *i))
        return(ft_strdup(""));
    if (!ft_isalpha(str[*i]) && str[*i] != '_')
        return (ft_strdup("$"));
    return(ft_find_value_env_new(str, i, data));
}
char *normal(char *str, int *i)
{
    int start;

    start = *i;
    while (str[*i] && str[*i] != '"' && str[*i] != '$' && str[*i] != '\'')
        (*i)++;
    return (ft_substr(str, start, *i - start));
}

char *ft_get_new_str_for_env_y(char *str, t_data *data)
{
    char *env_str;
    int i;

    i = 0;
    env_str = NULL;
    while (str[i])
    {
        if (str[i] == '\'')
            env_str = ft_strjoin_you(env_str, single_quote(str, &i));
        if (str[i] == '\"')
            env_str = ft_strjoin_you(env_str, double_quote(str, &i, data));
        if (str[i] == '$')
		{
            env_str = ft_strjoin_you(env_str, find_new_str_env_y(str, &i, data));
			data->status = 0;
		}
		else
            env_str = ft_strjoin_you(env_str, normal(str, &i));
    }
    free(str);
    return (env_str);
}
