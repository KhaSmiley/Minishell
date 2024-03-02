/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:14:19 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/02 02:17:05 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_find_dollar(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '$')
            count++;
        i++;
    }
    return (count);
}

char *expand_new_str(char *str, char *stock)
{
    char *new_str;
    char *stock;
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        while (str[i] && str[i] != '$')
        {
            new_str[j] = str[i];
            i++;
        }
        if (str[i] == '$')
        {
            ft_strlcat(new_str, stock, ft_strlen(new_str) + ft_strlen(stock) + 1);
        }
    }
    
}

int *find_key(t_token *tok)
{
    int i;
    t_token *tmp;

    i = 0;
    tmp = tok;
    while(tmp)
    {
        if (tmp->str[i] == '$')
            return (&tmp->str[i + 1]);
        tmp = tmp->next;
    }
    return (NULL);
}