/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:39 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/08 19:16:16 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_export	*ft_lstlast_export(t_export *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

void	ft_stock_export(t_export **lst, t_export *new_link)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new_link;
	else
		(ft_lstlast_export(*lst))->next = new_link;
}

void	print_list_export(t_export *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return ;
}
