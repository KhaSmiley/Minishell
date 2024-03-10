/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:22:06 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/10 23:22:16 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_tablen(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

int ft_find_malloc_key(char *str, int i)
{
    while(str[i] && (str[i] != ' ' && str[i] != '$'))
        i++;
    return (i);
}

// Trying to find the key so later i can find the value with it
// key is the string before the = in the env list
// ex : USER=kboulkri, key is USER and value is kboulkri

char *ft_find_key(char *str, int count)
{
    int i;
    int j;
    int y;
    char *key;

    i = 0;
    y = 1;
    key = NULL;
    while(str[i])
    {
        if (str[i] == '$' && y == count)
        {
            j = 0;
            i++;
            key = malloc(ft_find_malloc_key(str, i) + 1);
            while(str[i] && (str[i] != ' ' && str[i] != '$'))
                key[j++] = str[i++];
            key[j] = '\0';
            break ;
        }
        else if (str[i] == '$' && y != count)
            y++;
        i++;
    }
    return (key);
}

int ft_strlen_from_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}

// Function to copy the envp and not to use the original one so we can modify it with export and set and unset

char **ft_envp_copy(char **envp)
{
    char **envp_cpy;
    int i;

    i = 0;
    envp_cpy = malloc(sizeof(char *) * (ft_tablen(envp) + 1));
    if (!envp_cpy)
        return (NULL);
    while (envp[i])
    {
        envp_cpy[i] = ft_strdup(envp[i]);
        if (!envp_cpy[i])
            return (NULL);
        i++;
    }
    envp_cpy[i] = NULL;
    return (envp_cpy);
}
