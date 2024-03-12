/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 03:40:10 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/12 22:41:28 by kboulkri         ###   ########.fr       */
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
        ft_printf("WORD : %s TYPE : %d\n", lst->str, lst->type);
        lst = lst->next;
    }
    return ;
}
void free_list(t_token **tok)
{
	t_token	*tmp;
	t_token	*lst;

	if (!tok || !*tok)
		return ;
	lst = *tok;
	while (lst->env->next != NULL)
	{
		tmp = (lst)->next;
		free((lst)->env->key);
		free((lst)->env->value);
		free(lst);
		lst = tmp;
	}
	while (*tok)
	{
		tmp = (*tok)->next;
		free((*tok)->str);
		free(*tok);
		*tok = tmp;
	}
}