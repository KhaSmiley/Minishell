/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:14:19 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/10 23:24:55 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// Same functions as the lst_utils but for the env list

t_env *ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_stock_env(t_env **lst, t_env *new_link)
{
	if (!lst || !new_link)
		return ;
	if (!*lst)
		*lst = new_link;
	else
		(ft_lstlast_env(*lst))->next = new_link;
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*new;

	if (!key || !value)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
    new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void print_list_env(t_token *lst)
{
	printf("PRINTING ENV LIST\n");
	if (!lst)
		return ;
	while(lst)
	{
		ft_printf("KEY : %s VALUE : %s\n", lst->env->key, lst->env->value);
		lst = lst->next;
	}
	return ;
}
