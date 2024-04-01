/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 03:45:20 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/01 20:03:42 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	to_builtin_or_not_to_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

char	*find_first_cmd(t_token **tok)
{
	t_token	*tmp;

	tmp = *tok;
	while (tmp)
	{
		if (tmp->type == WORD)
			return (tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}

int	one_built_in(char **builtin, t_token *tok, t_data *data)
{
	int	std_fd[2];

	data->builtin = builtin;
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	redirection(data, 0);
	redir_files(tok, 0, data);
	lets_builtin(data, builtin, data->envp_cpy);
	if (ft_strcmp(builtin[0], "unset") == 0)
		return (free(builtin[0]), 0);
	free_tab(builtin);
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	close(std_fd[0]);
	close(std_fd[1]);
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

int	check_echo_option(char **args, int i, int j)
{
	while (args[++i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '-')
				j++;
			if (args[i][j] != 'n')
				return (i - 1);
			if (args[i][j + 1] != 'n' && args[i][j + 1] != '\0'
				&& (args[i][j + 1] != ' ' || args[i][j + 1] != '\t'))
				return (i - 1);
			while (args[i][j] == 'n')
			{
				if (args[i][j] == '\0')
					break ;
				j++;
			}
			if (args[i][j] != 'n' && args[i][j] != '\0')
				return (i - 1);
		}
	}
	return (i - 1);
}
