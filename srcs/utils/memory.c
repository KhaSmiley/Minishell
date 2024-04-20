/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:55:28 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/09 07:46:45 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_tok(t_token **tok)
{
	t_token	*tmp;

	if (!tok || !*tok)
		return ;
	while (*tok)
	{
		tmp = *tok;
		*tok = (*tok)->next;
		if (tmp->str)
		{
			ft_free((void **)&tmp->str);
		}
		ft_free((void **)&tmp);
	}
}

void	free_export(t_export *lst)
{
	t_export	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_data	*simpleton(void)
{
	static t_data	data;

	return (&data);
}
