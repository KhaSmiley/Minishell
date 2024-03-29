/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:21:27 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/27 03:00:51 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_if_key_exist_export(t_export *lst, char *key)
{
    while (lst)
    {
        if (!ft_strncmp(lst->key, key, ft_strlen(lst->key)))
            return (1);
        lst = lst->next;
    }
    return (0);
}

t_export *ft_lstlast_export(t_export *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_stock_export(t_export **lst, t_export *new_link)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new_link;
	else
		(ft_lstlast_export(*lst))->next = new_link;
}

t_export	*ft_lstnew_export(char *key, char *value)
{
	t_export	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->key = key;
    new->value = value;
	new->next = NULL;
	return (new);
}

void free_key_export(void *delete)
{
    free(delete);
}