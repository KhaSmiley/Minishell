/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:46:52 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/25 01:57:47 by lbarry           ###   ########.fr       */
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
		if (tmp && (tmp->type == LESS || tmp->type == GREATER))
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
        if (tmp && tmp->type == WORD)
        {
            if (tmp->next && tmp->str[0] == '\0')
            {
                tmp = tmp->next;
                if (tmp->type == PIPE)
                    break;
            }
            tab[i] = ft_strdup(tmp->str);
            i++;
        }
        tmp = tmp->next;
    }
    tab[i] = NULL;
    return (tab);
}

int	get_infile(t_data *data, t_token **tok)
{
	t_token *tmp;

	tmp = *tok;
    while (tmp && tmp->type != PIPE)
    {
        if (tmp->type == LESS)
		{
			tmp = tmp->next;
			data->infile = ft_strdup(tmp->str);
			if (!data->infile)
				return (0);
		}
        tmp = tmp->next;
    }
	return (1);
}

int	get_outfile(t_data *data, t_token **tok)
{
	t_token *tmp;

	tmp = *tok;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == GREATER)
		{
			tmp = tmp->next;
			data->outfile = ft_strdup(tmp->str);
			if (!data->outfile)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
