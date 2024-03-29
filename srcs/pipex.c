/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/29 04:44:09 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_fds(t_data *data)
{
	if (data->tmp_fd > 0)
		close(data->tmp_fd);
	if (data->pipe_fd[0] > 0)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] > 0)
		close(data->pipe_fd[1]);
	if (data->fd_in > 0)
		close(data->fd_in);
	if (data->fd_out > 0)
		close(data->fd_out);
}

int	open_fds(int i, t_data *data, t_token **tok)
{
	printf("i = %d\n", i);
	printf("nb_cmd = %d\n", data->nb_cmd);
	if (!get_infile(data, tok, i))
		return (0);
	printf("last infile = %s\n", data->infile);
	if (!get_outfile(data, tok, i))
	{
		printf("hellooooo no outfile\n");
		return (0);
	}
	printf("last outfile = %s\n", data->outfile);
	return (1);
}

void	redirection(t_data *data, int i)
{
	printf("i = %d\n", i);
	printf("nb_cmd = %d\n", data->nb_cmd);
	if (data->infile)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (i != 0)
	{
		dup2(data->tmp_fd, STDIN_FILENO);
		close(data->tmp_fd);
	}
	if (i != data->nb_cmd - 1)
	{
		close(data->pipe_fd[0]);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
	if (data->outfile)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void	child_process(t_data *data, t_token **tok, int i)
{
	char	**cmd;
	char	*path;

	cmd = tok_to_tab(tok, i);
	// printf("******printing tok\n");
	// print_list(*tok);
	// printf("******printing cmd\n");
	// print_tab(cmd);
	if (!cmd)
		return (free_tab(cmd), exit(1));
	if (!cmd[0])
		return (ft_printf("minishell: cmd[0] empty, tok 2 tab failed\n"), free_tab(cmd),  free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	if (to_builtin_or_not_to_builtin(cmd[0]))
	{
		lets_builtin(cmd, data->envp_cpy, tok);
		return (free_tab(cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(0));
	}
	// if (!open_fds(i, data, tok))
	// 	return (free_tab(cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	redirection(data, i);
	// when do we use func close fds?
	path = complete_path(data, cmd[0]);
	if (!path)
		return (ft_printf("minishell: %s: command path not found\n", cmd[0]), free_tab(cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	// printf("hellooo I'm here!\n");
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
		pipe(data->pipe_fd);
		if (data->pipe_fd[0] == -1 || data->pipe_fd[1] == -1)
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
	close(data->pipe_fd[0]);
	return (0);
}
