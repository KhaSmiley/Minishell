/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 06:00:30 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 19:22:24 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_unset(t_export *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	ft_delone_unset(t_export **env, char *key)
{
	t_export	*tmp;
	t_export	*prev;

	prev = *env;
	if (env && !ft_strcmp((*env)->key, key))
	{
		tmp = (*env);
		(*env) = (*env)->next;
		ft_free_unset(tmp);
		free(key);
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
		ft_free_unset(tmp);
	}
}

void	ft_unset(t_data *data, char **args)
{
	int	i;

	i = 1;
	if (!args[i])
		return ;
	if (!data->env_export)
		return ;
	while (args[i])
	{
		ft_delone_unset(&data->env_export, args[i]);
		i++;
	}
}
