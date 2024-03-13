/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_after_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:06:40 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/13 14:46:46 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_get_new_str_for_env(char *str, t_token *tok)
{
    char *env_str;
    char *add_str;
    int i;

    i = 0;
    env_str = NULL;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
            printf("RETURN EXIT STATUS\n");
        else if (str[i] == '$')
        {
            i++;
            env_str = ft_strjoin_gnl(env_str, tok->env->value);
            i = i + ft_strlen(tok->env->key) - 1;
            tok->env = tok->env->next;
        }
        else
        {
            add_str = ft_substr(str, i, 1);
            env_str = ft_strjoin_gnl(env_str, add_str);
            free(add_str);
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