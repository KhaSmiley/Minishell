/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 05:31:16 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/02 01:23:48 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int ft_strlen_from_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}

char *ft_find_var(char *var, char **envp_cpy)
{
    int i;
    char *stock;

    i = 0;
    // int j = 0;
    while (envp_cpy[i])
    {
        if (ft_strncmp(envp_cpy[i], var, ft_strlen(var)) == 0)
        {
            if (envp_cpy[i][ft_strlen(var)] == '=')
            {
                stock = ft_substr(envp_cpy[i], ft_strlen_from_char(envp_cpy[i], '=') + 1, ft_strlen(envp_cpy[i]) - ft_strlen(var) - 1);
                if (!stock)
                    return (NULL);
                return (stock);
            }    
        }
        i++;
    }
    return (ft_printf("$%s doesn't exist", var), NULL);
}

char **ft_cpy_envp(char **envp)
{
    char **envp_cpy;
    int i;

    i = 0;
    while (envp[i])
        i++;
    envp_cpy = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i])
    {
        envp_cpy[i] = ft_strdup(envp[i]);
        i++;
    }
    envp_cpy[i] = NULL;
    return (envp_cpy);
}

void ft_expand(char **envp)
{
    int i;
    char **envp_cpy;
    // char *stock;
    
    i = 0;
    envp_cpy = ft_cpy_envp(envp);
    free_tab(envp_cpy);
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argv;
//     if (argc > 2)
//         ft_expand(argv, envp);
//     return (0);
// }