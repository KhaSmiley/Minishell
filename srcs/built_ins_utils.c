/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:04:34 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/24 21:22:45 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_first_cmd(t_token **tok)
{
	t_token *tmp;

	tmp = *tok;
	while (tmp)
	{
		if (tmp->type == WORD)
			return (tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}

int	one_built_in(char **builtin, t_data *data, t_token **tok)
{
	lets_builtin(builtin, data->envp_cpy, tok);
	free_tab(builtin);
	return (0);
}

char	*get_home_env(char **envp_cpy)
{
	int		i;

	i = 0;
	while (envp_cpy[i])
	{
		if (!ft_strncmp(envp_cpy[i], "HOME=", 5))
			return (envp_cpy[i] + 5);
		i++;
	}
	return (NULL);
}

int	check_echo_option(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '-')
				j++;
			if (args[i][j] != 'n')
				return (i - 1);
			if (args[i][j + 1] != 'n' && args[i][j + 1] != '\0' && args[i][j + 1] != ' ')
				return (i - 1);
			while (args[i][j] == 'n')
			{
				if (args[i][j] != 'n' && args[i][j] != '\0')
					return (i - 1);
				else if (args[i][j] == '\0')
					break ;
				j++;
			}
		}
		i++;
	}
	return (i - 1);
}
