/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:21:27 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 19:17:51 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_find_key_export(char *str)
{
	int		i;
	int		j;
	char	*key;

	key = NULL;
	i = 0;
	j = 0;
	key = ft_calloc(sizeof(char), ft_find_malloc_key(str, i) + 1);
	while (str[i] && (ft_isalnum_env(str[i])))
		key[j++] = str[i++];
	key[j] = '\0';
	return (key);
}

int	check_if_key_exist_export(t_export *lst, char *key)
{
	while (lst)
	{
		if (!ft_strncmp(lst->key, key, ft_strlen(lst->key)))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	free_key_export(void *delete)
{
	free(delete);
}

void	ft_free_in_export_func(t_export *tmp, char *key)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	free(key);
}

void	ft_delone_export(t_export **env, char *key)
{
	t_export	*tmp;
	t_export	*prev;

	prev = *env;
	if (env && !ft_strcmp((*env)->key, key))
	{
		tmp = (*env);
		(*env) = (*env)->next;
		ft_free_in_export_func(tmp, key);
		return ;
	}
	tmp = (*env)->next;
	while (tmp && ft_strcmp(tmp->key, key))
	{
		prev = prev->next;
		tmp = tmp->next;
	}
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		prev->next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(key);
}
