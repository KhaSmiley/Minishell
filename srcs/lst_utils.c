/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 03:40:10 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/14 17:20:37 by lbarry           ###   ########.fr       */
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

	if (!content)
		return (NULL);
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
	t_token	*next;

	if (!tok || !*tok)
		return ;
	tmp = *tok;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->env)
		{
			if (tmp->env->key)
				free(tmp->env->key);
			if (tmp->env->value)
				free(tmp->env->value);
		}
		if (tmp->str)
			free(tmp->str);
		//free(tmp);
		tmp = next;
	}
}
