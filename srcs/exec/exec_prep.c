/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/07 05:56:05 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *find_curr_tok_pipe(t_token **tok, int nb_pipe)
{
	t_token *tmp;
	int count_pipe;
	
	count_pipe = 0;
	tmp = *tok;
	while (tmp && count_pipe != nb_pipe)
	{
		if (tmp->type == PIPE)
			count_pipe++;
		tmp = tmp->next;
	}
	return (tmp);
}

int	ft_count_pipe(t_token *tok)
{
	int		count;
	t_token	*tmp;

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

int	find_malloc_tok_to_tab(t_token **tok, int nb_pipe)
{
	t_token	*tmp;
	t_token *tmp_curr;
	int		size_malloc;

	tmp = *tok;
	size_malloc = 0;
	tmp_curr = find_curr_tok_pipe(tok, nb_pipe);
	while (tmp_curr && tmp_curr->type != PIPE)
	{
		if (tmp_curr->type == GREATER || tmp_curr->type == LESS || tmp_curr->type == DGREATER
			|| tmp_curr->type == DLESS)
			tmp_curr = tmp_curr->next;
		else if (tmp_curr->type == WORD)
		{
			if (tmp_curr->next && tmp_curr->str[0] == '\0')
			{
				tmp_curr = tmp_curr->next;
				if (tmp_curr->type == PIPE)
					break ;
			}
			if (!tmp_curr->str)
				size_malloc++;
			else
				size_malloc++;
		}
		tmp_curr = tmp_curr->next;
	}
	return (size_malloc);
}

char	**tok_to_tab(t_token **tok, int nb_pipe)
{
	t_token	*tmp;
	t_token *tmp_curr;
	char	**tab;
	int		i;  
	int		size;

	i = 0;
	size = find_malloc_tok_to_tab(tok, nb_pipe);
	if (size == 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tmp = *tok;
	tmp_curr = find_curr_tok_pipe(tok, nb_pipe);
	while (tmp_curr && tmp_curr->type != PIPE)
	{
		if (tmp_curr->type == GREATER || tmp_curr->type == LESS || tmp_curr->type == DGREATER
			|| tmp_curr->type == DLESS)
			tmp_curr = tmp_curr->next;
		else if (tmp_curr->type == WORD)
		{
			if (tmp_curr->next && tmp_curr->str[0] == '\0')
			{
				tmp_curr = tmp_curr->next;
				if (tmp_curr->type == PIPE)
					break ;
			}
			if (!tmp_curr->str)
				tab[i++] = ft_strdup("");
			else
				tab[i++] = ft_strdup(tmp_curr->str);
		}
		tmp_curr = tmp_curr->next;
	}
	if (i == 0)
		return (NULL);
	tab[i] = NULL;
	return (tab);
}
