/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/29 06:33:17 by lbarry           ###   ########.fr       */
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
}

void	redirection(t_data *data, int i)
{
	(void)i;
	(void)data;
	// if (data->infile_fd)
	// {
	// 	dup2(data->infile_fd, 0);
	// 	close(data->infile_fd);
	// }
	// if (data->outfile_fd)
	// {
	// 	dup2(data->outfile_fd, 1);
	// 	close(data->outfile_fd);
	// }
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
void ft_find_outfile(t_data *data, t_token **tok)
{
	t_token *tmp;

	tmp = *tok;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == GREATER)
		{
			data->outfile_fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(data->outfile_fd, 1);
			close(data->outfile_fd);
			printf("JE SUIS OUTFILE%s -> %d\n", tmp->next->str, data->outfile_fd);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

void ft_find_infile(t_data *data, t_token **tok)
{
	t_token *tmp;

	tmp = *tok;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LESS)
		{
			data->infile_fd = open(tmp->next->str, O_RDONLY);
			dup2(data->infile_fd, 0);
			close(data->infile_fd);
			printf("JE SUIS INFILE%s -> %d\n", tmp->next->str, data->infile_fd);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

void	child_process(t_data *data, t_token **tok, int i)
{
	char	**cmd;
	char	*path;

	cmd = tok_to_tab(tok, i);
	//print_tab(cmd);
	if (!cmd)
		return (free_tab(cmd), exit(1));
	if (!cmd[0])
		return (ft_printf("minishell: cmd[0] empty, tok 2 tab failed\n"), free_tab(cmd),  free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	if (to_builtin_or_not_to_builtin(cmd[0]))
	{
		lets_builtin(cmd, data->envp_cpy);
		return (free_tab(cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(0));
	}
	path = complete_path(data, cmd[0]);
	if (!path)
		return (ft_printf("minishell: %s: command path not found\n", cmd[0]), free_tab(cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	ft_find_infile(data, tok);
	ft_find_outfile(data, tok);
	redirection(data, i);
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
