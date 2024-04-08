/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:30:53 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 05:09:48 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_find_nb_args_exit(t_token **tok)
{
	int		i;
	t_token	*tmp;

	tmp = *tok;
	i = 0;
	while (tmp)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	check_digits(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_isdigit(args[i]) || i > 18)
			return (0);
		i++;
	}
	return (1);
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

void	print_list_export(t_export *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return ;
}
