/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:46:52 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/20 11:46:47 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_count_pipe (t_token *tok)
{
    int count;
    t_token *tmp;

    count = 1;
    tmp = tok;
    while (tmp)
    {
        if (tmp->type == PIPE)
            count++;
        tmp = tmp->next;
    }
    return (count);
}

char **tok_to_tab(t_token **tok, int nb_pipe)
{
    t_token *tmp;
    char **tab;
    int i;
    int count_pipe;

    count_pipe = 0;
    tmp = *tok;
    i = 0;
    tab = malloc(sizeof(char *) * (10));
    while (tmp && count_pipe != nb_pipe)
    {
        if (tmp->type == PIPE)
            count_pipe++;
        tmp = tmp->next;
    }
    while (tmp && tmp->type != PIPE)
    {
        if (tmp->type == WORD)
        {
            if (tmp->str[0] == '\0' && tmp->next)
                tmp = tmp->next;
            tab[i] = ft_strdup(tmp->str);
            i++;
        }
        tmp = tmp->next;
    }
    tab[i] = NULL;
    return (tab);
}