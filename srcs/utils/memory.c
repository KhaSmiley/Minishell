/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:55:28 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/07 18:14:23 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			free(tmp->str);
			tmp->str = NULL;
		}
		free(tmp);
		tmp = NULL;
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
