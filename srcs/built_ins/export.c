/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:13:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 19:17:38 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_find_value_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_strdup(&str[i + 1]));
}

int	ft_check_syntax_key(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (1);
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum_env(str[i]) && str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(t_data *data, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_check_syntax_key(args[i]))
		{
			ft_printf("export: `%s': not a valid identifier\n", args[i]);
			data->status = 1;
		}
		else if (ft_strchr(args[i], '='))
		{
			if (check_if_key_exist_export(data->env_export, args[i]))
			{
				ft_delone_export(&data->env_export,
					ft_find_key_export(args[i]));
			}
			ft_stock_export(&data->env_export,
				ft_lstnew_export(ft_find_key_export(args[i]),
					ft_find_value_export(args[i])));
		}
		i++;
	}
	return ;
}
