/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:14:19 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/08 21:37:50 by kboulkri         ###   ########.fr       */
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

		return ;
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
