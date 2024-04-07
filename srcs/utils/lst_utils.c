/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 03:40:10 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/07 18:25:26 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_stock(t_token **lst, t_token *new_link)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new_link;
	else
		(ft_lstlast(*lst))->next = new_link;
}

t_token	*ft_lstnew(char *content, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	print_list(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("string: %s\ntype = %d\n", lst->str, lst->type);
		lst = lst->next;
	}
	return ;
}

int	ft_lstsize(t_export *env)
{
	t_export	*tmp;
	int			i;

	i = 0;
	if (!env)
		return (i);
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
