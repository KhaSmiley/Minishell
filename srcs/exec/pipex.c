/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/30 04:39:07 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quit_file_error(int fd, t_token *tok, t_data *data)
{
	fprintf(stderr, "%d -> Error FD\n", fd);
	free_tok(&tok);
	free_envp_cpy(data->envp_cpy);
	if (data->builtin)
		free_tab(data->builtin);
	if (data->cmd)
		free_tab(data->cmd);
	close_fds(data);
	exit(0);
}
void	close_fds(t_data *data)
{
	if (data->tmp_fd > 0)
		close(data->tmp_fd);
	if (data->pipe_fd[0] > 0)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] > 0)
		close(data->pipe_fd[1]);
}

void	redir_files(t_token *tok, int i, t_data *data)
{
	int		fd;
	int		nb_pipe;
	t_token	*tmp;

	tmp = tok;
	nb_pipe = 0;
	fd = -2;
	while (tmp)
	{
		if (nb_pipe == i)
			break ;
		if (tmp->type == PIPE)
			nb_pipe++;
		tmp = tmp->next;
	}
	while(tmp && tmp->type != PIPE)
	{
		if (tmp->type == GREATER)
			fd = open(tmp->next->str, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (tmp->type == DGREATER)
			fd = open(tmp->next->str, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (tmp->type == LESS)
			fd = open(tmp->next->str, O_RDONLY);
		if (fd == -1)
			quit_file_error(fd, tok, data);
		if (tmp->type == GREATER || tmp->type == DGREATER)
			dup2(fd, STDOUT_FILENO);
		else if (tmp->type == LESS)
			dup2(fd, STDIN_FILENO);
		tmp = tmp->next;
	}
}

void	redirection(t_data *data, t_token *tok, int i)
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
	redir_files(tok, i, data);
}

void	child_process(t_data *data, t_token **tok, int i)
{
	char	*path;

	data->cmd = tok_to_tab(tok, i);
	if (!data->cmd)
		return (free_tab(data->cmd), exit(1));
	if (!data->cmd[0])
		return (ft_printf("minishell: cmd[0] empty, tok 2 tab failed\n"), free_tab(data->cmd),  free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	redirection(data, *tok, i);
	if (to_builtin_or_not_to_builtin(data->cmd[0]))
	{
		lets_builtin(data, data->cmd, data->envp_cpy);
		return (free_tab(data->cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(0));
	}
	path = complete_path(data, data->cmd[0]);
	if (!path)
		return (ft_printf("minishell: %s: command path not found\n", data->cmd[0]), free_tab(data->cmd), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(1));
	if (path)
		execve(path, data->cmd, data->envp_cpy);
	return (free_tab(data->cmd), free(path), free_tok(tok), free_envp_cpy(data->envp_cpy), exit(0));
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
	t_heredoc *here_docs;

	here_docs = exec_here_docs(data, tok);
	print_list_here_doc(here_docs);
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
