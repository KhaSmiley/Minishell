/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 03:45:20 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/05 19:26:53 by lbarry           ###   ########.fr       */
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
	else if (!ft_strcmp(cmd, "exit"))
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
	t_heredoc	*h_docs;

	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	data->builtin = builtin;
	h_docs = here_doc_launch(data, &tok);
	if (!redir_files(tok, 0, h_docs, data))
	{
		dup2(data->std_fd[0], STDIN_FILENO);
		dup2(data->std_fd[1], STDOUT_FILENO);
		close(data->std_fd[0]);
		close(data->std_fd[1]);
		return (0);
	}
	lets_builtin_no_fork(data, builtin, &tok);
	if (ft_strcmp(builtin[0], "unset") == 0)
		return (free(builtin[0]), 1);
	free_tab(builtin);
	dup2(data->std_fd[0], STDIN_FILENO);
	dup2(data->std_fd[1], STDOUT_FILENO);
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	return (1);
}

char	*get_home_env(t_export *env)
{
	t_export	*tmp;
	int			i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
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
			if (args[i][j + 1] != 'n' && args[i][j + 1] != '\0' && (args[i][j
					+ 1] != ' ' || args[i][j + 1] != '\t'))
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
