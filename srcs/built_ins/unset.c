/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 06:00:30 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/30 04:32:13 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delone_unset(t_export **env, char *key)
{
	t_export *tmp;

	t_export *prev = *env;
	// si ma tete == le noeud a supprimer
	if (env && !ft_strcmp((*env)->key, key))
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		free(key);
		return ;
	}
	tmp = (*env)->next;
	// je boucle tant que je trouve pas ma key
	while (tmp && ft_strcmp(tmp->key, key))
	{
		prev = prev->next;
		tmp = tmp->next;
	}
	// si je la trouve
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		prev->next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void ft_unset(t_data *data, char **args)
{
	int i;

	ft_envp_copy_export(data);
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
