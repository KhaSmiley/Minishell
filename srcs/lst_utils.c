/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 03:40:10 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/13 12:19:28 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *ft_lstlast(t_token *lst)
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

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->str = content;
    new->type = type;
	new->next = NULL;
	return (new);
}
void print_list(t_token *lst)
{
    if (!lst)
		return ;
    while(lst)
    {
        ft_printf("%s", lst->str);
        lst = lst->next;
    }
	ft_printf("\n");
    return ;
}
void free_list(t_token **tok)
{
	t_token	*tmp;
	t_token	*lst;
	t_token *tmp2;

	if (!tok || !*tok)
		return ;
	lst = *tok;
	while (lst)
	{
		tmp = (lst)->next;
		if (lst->env)
		{
			if (lst->env->key)
				free((lst)->env->key);
			if (lst->env->value)
				free((lst)->env->value);
		}
		lst = tmp;
	}
	while (*tok)
	{
		tmp = (*tok)->next;
		tmp2 = *tok;
		free(tmp2->str);
		free(tmp2);
		*tok = tmp;
	}
}
