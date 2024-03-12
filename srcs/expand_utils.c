/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:14:19 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/12 22:07:33 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// Same functions as the lst_utils but for the env list

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
	if (!*lst && new_link)
		*lst = new_link;
	else if (new_link)
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
	if (!lst)
		return ;
	while(lst)
	{
		if (lst->env)
		{
			t_env *env_ptr = lst->env;
			while (env_ptr)
			{
				if (env_ptr->key && env_ptr->value)
				{	
					ft_printf("KEY : %s VALUE : %s\n", env_ptr->key, env_ptr->value);
					env_ptr = env_ptr->next;
				}
				else
					break ;
			}
		}
		lst = lst->next;
	}
	return ;
}

void free_list_env(t_env *env)
{
    t_env   *temp;

	if (!env)
		return ;
    while (env)
    {
        temp = env;
        if (env->next != NULL)
			env = env->next;
		else
			free(env);
        // free(temp->key);
        // free(temp->value);
        // free(temp);
    }
}