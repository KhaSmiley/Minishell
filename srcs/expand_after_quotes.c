/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_after_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:06:40 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/15 22:04:52 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// input --> new input with expands
// from bonjour je suis $USER$HAPPY
// to bonjour je suis kboulkri$HAPPY

char *ft_get_new_str_for_env(char *str, t_token *tok)
{
    char *env_str;
    char *add_str;
    int i;

    i = 0;
    env_str = NULL;
	t_env *tmp_env = tok->env;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
            printf("RETURN EXIT STATUS\n");
        else if (str[i] == '$')
        {
            i++;
            if (tmp_env->value[0] == '\0')
            {
                i--;
                add_str = ft_substr(str, i, 1);
                env_str = ft_strjoin_gnl(env_str, add_str);
                free(add_str);
            }
            else if (tmp_env->value)
            {
                env_str = ft_strjoin_gnl(env_str, tmp_env->value);
                i = i + ft_strlen(tmp_env->key) - 1;
            }
            tmp_env = tmp_env->next;
        }
        else
        {
            add_str = ft_substr(str, i, 1);
            env_str = ft_strjoin_gnl(env_str, add_str);
            free(add_str);
        }
        i++;
    }
	free(str);
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
