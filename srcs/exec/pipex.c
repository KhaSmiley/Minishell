/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/03 19:23:30 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quit_file_error(int fd, t_token *tok, t_data *data)
{
	(void) fd;
	free_tok(&tok);
	if (data->builtin)
		free_tab(data->builtin);
	if (data->cmd)
		free_tab(data->cmd);
	close_fds(data);
	exit(1);
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

void	redir_files(t_token *tok, int i,t_heredoc *h_docs, t_data *data)
{
	int		fd;
	int		nb_pipe;
	t_token	*tmp;

	tmp = tok;
	nb_pipe = 0;
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
		if (tmp->type == WORD)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type == GREATER)
			fd = open(tmp->next->str, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (tmp->type == DGREATER)
			fd = open(tmp->next->str, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (tmp->type == LESS)
			fd = open(tmp->next->str, O_RDONLY);
		else if (tmp->type == DLESS)
			fd = find_heredoc(h_docs, ft_lstsize_hdoc(h_docs), tmp);
		if (fd == -1)
			quit_file_error(fd, tok, data);
		if (tmp->type == GREATER || tmp->type == DGREATER)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		if (tmp->type != DLESS)
			close(fd);
		tmp = tmp->next;
	}
	close_here_docs(h_docs, ft_lstsize_hdoc(h_docs));
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

int ft_lstsize(t_export *env)
{
    t_export *tmp;
    int i;

    i = 0;
    if (!env)
        return (i);
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}
char **ft_envp_copy_to_tab(t_data *data)
{
    t_export *tmp;
    char *new_str;
    char **tab;
    int size;
    int i;

    i = 0;
    tmp = data->env_export;
    size = ft_lstsize(data->env_export);
	tab = NULL;
    tab = malloc(sizeof(char *) * (size + 1));
    while(tmp)
    {
        new_str = NULL;
        new_str = ft_strjoin(tmp->key, "=");
        new_str = ft_strjoin_gnl(new_str, tmp->value);
        tab[i] = ft_strdup(new_str);
        free(new_str);
        tmp = tmp->next;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

void	child_process(t_data *data, t_token **tok, t_heredoc *h_docs, int i)
{
	char	*path;
	char **tab;

	(void)h_docs;

	data->cmd = tok_to_tab(tok, i);
	redirection(data, i);
	redir_files(*tok, i, h_docs, data);
	if (!data->cmd)
		return (free_tok(tok), free(data->input), free_export(data->env_export), exit(0));
	if (!data->cmd[0])
		return (ft_printf("minishell: : command not found\n"), free_tab(data->cmd),  free_tok(tok), free_export(data->env_export), exit(127));
	if (to_builtin_or_not_to_builtin(data->cmd[0]))
	{
		lets_builtin(data, data->cmd);
		return (free_tab(data->cmd), free_tok(tok), free_export(data->env_export), exit(0));
	}
	path = complete_path(data, data->cmd[0]);
	if (!path)
		return (ft_printf("minishell: %s: command path not found\n", data->cmd[0]), free_tab(data->cmd), free_tok(tok), free_export(data->env_export), exit(127));
	tab = ft_envp_copy_to_tab(data);
	if (path)
		execve(path, data->cmd, tab);
	return (printf("COMMAND NOT FOUND\n"), free_tab(data->cmd), free(path), free_tok(tok), free_export(data->env_export), exit(127));
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
	t_heredoc *here_docs;

	here_docs = exec_here_docs(data, tok);
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
			child_process(data, tok, here_docs, i);
		else
			parent_process(data, i);
	}
	i = 0;
	while (i < data->nb_cmd)
	{
		waitpid(data->pid[i++], &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
	}
	close(data->pipe_fd[0]);
	return (0);
}
