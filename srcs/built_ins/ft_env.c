/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:30:53 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/09 16:07:38 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_home_env(t_export *env)
{
	t_export	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
			return ((tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_env(t_data *data)
{
	print_list_export(data->env_export);
	return (1);
}

void	ft_envp_copy_export(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_stock_export(&data->env_export,
			ft_lstnew_export(ft_find_key_export(envp[i]),
				ft_find_value_export(envp[i])));
		i++;
	}
}
