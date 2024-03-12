/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_after_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:06:40 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/12 21:06:43 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_get_new_str_for_env(char *str, t_token *tok)
{
    char *env_str;
    int i;

    i = 0;
    env_str = NULL;
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            env_str = ft_strjoin_gnl(env_str, tok->env->value);
            printf("env_str = %s\n", env_str);
            i = i + ft_strlen(tok->env->key) - 1;
        }
        else
        {
            env_str = ft_strjoin_gnl(env_str, ft_substr(str, i, 1));
            printf("env_str = %s\n", env_str);
        }
        i++;
    }
    return (env_str);
}

void find_str_to_expand(t_token **tok)
{
    t_token *tmp;

    tmp = *tok;
    while (tmp)
    {    
        if (tmp->type == WORD)
        {
            if (ft_strchr(tmp->str, '$'))
                tmp->str = ft_get_new_str_for_env(tmp->str, tmp);
        }
        tmp = tmp->next;
    }
}