/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/21 15:17:40 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

void	redirection(t_data *data, int i)
{
	if (i != 0)
	{
		dup2(data->tmp_fd, 0);
		close(data->tmp_fd);
	}
	if (i != data->nb_cmd - 1)
		dup2(data->pipe_fd[1], 1);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void	child_process(t_data *data, t_token **tok, int i)
{
	char	**cmd;
	char	*path;

	redirection(data, i);
	cmd = tok_to_tab(tok, i);
	if (!cmd)
		return (free_tab(cmd), exit(1));
	if (!cmd[0])
		return (ft_printf("minishell: cmd[0] empty, tok 2 tab failed\n"), free_tab(cmd),  free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	path = complete_path(data, cmd[0]);
	if (!path)
		return (ft_printf("minishell: %s: command path not found\n", cmd[0]), free_tab(cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	print_tab(cmd);
	// 1 cmd only and builtin = execute builtin in parent
	// if (to_builtin_or_not_to_builtin(cmd))
	// {
	// 	lets_builtin(cmd, data->envp_cpy);
	// 	return (free_tab(cmd), free(path), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(0));
	// }
	if (path)
		execve(path, cmd, data->envp_cpy);
	return (free_tab(cmd), free(path), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(0));
}

void	parent_process(t_data *data, int i)
{
	close(data->pipe_fd[1]);
	if (i != 0)
		close(data->tmp_fd);
	data->tmp_fd = data->pipe_fd[0];
}

int	exec_pipe(t_data *data, t_token **tok)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->nb_cmd)
	{
		if (pipe(data->pipe_fd) == -1)
			return (perror("Error pipe"), 0);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (perror("Error fork"), 0);
		if (data->pid[i] == 0)
			child_process(data, tok, i);
		else
			parent_process(data, i);
	}
	i = 0;
	while (i < data->nb_cmd)
		waitpid(data->pid[i++], &status, 0);
	return (0);
}
