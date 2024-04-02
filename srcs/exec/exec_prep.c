/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/02 04:12:37 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int ft_count_pipe (t_token *tok)
{
    int count;
    t_token *tmp;

    count = 0;
    tmp = tok;
	if (!tmp)
		return (0);
    while (tmp)
    {
        if (tmp->type == PIPE)
            count++;
        tmp = tmp->next;
    }
	if (count > 0)
		count++;
	else if (count == 0)
		count = 1;
    return (count);
}

char **tok_to_tab(t_token **tok, int nb_pipe)
{
    t_token *tmp;
    char **tab;
    int i;
    int count_pipe;
    count_pipe = 0;
    i = 0;

    tab = malloc(sizeof(char *) * (10));
	if (!tab)
	{
		ft_printf("tok to tab malloc error\n");
		return (NULL);
	}
    tmp = *tok;
    while (tmp && count_pipe != nb_pipe)
    {
        if (tmp->type == PIPE)
            count_pipe++;
        tmp = tmp->next;
    }
    while (tmp && tmp->type != PIPE)
    {
		if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
			tmp = tmp->next;
        else if (tmp->type == WORD)
        {
            if (tmp->next && tmp->str[0] == '\0')
            {
                tmp = tmp->next;
                if (tmp->type == PIPE)
                    break;
            }
            tab[i++] = ft_strdup(tmp->str);
        }
        tmp = tmp->next;
    }
    tab[i] = NULL;
    return (tab);
}

