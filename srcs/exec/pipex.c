/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/07 02:02:31 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, t_token **tok, t_heredoc *h_docs, int i)
{
	char	*path;
	char	**tab;

	(void)h_docs;
	data->cmd = tok_to_tab(tok, i);
	redirection(data, i);
	if (!redir_files(*tok, i, h_docs, data))
		return (free_export(data->env_export), exit(1));
	if (!data->cmd)
		return (free_tok(tok), free(data->input), free_export(data->env_export),
			exit(0));
	if (!data->cmd[0])
		return (ft_printf("minishell: : command not found\n"),
			free_tab(data->cmd), free_tok(tok), free_export(data->env_export),
			exit(127));
	if (to_builtin_or_not_to_builtin(data->cmd[0]))
	{
		lets_builtin(data, data->cmd, tok);
		return (free_tab(data->cmd), free_tok(tok),
			free_export(data->env_export), exit(0));
	}
	path = complete_path(data, data->cmd[0]);
	if (!path)
		return (ft_printf("minishell: %s: command not found\n", data->cmd[0]),
			free_tab(data->cmd), free_tok(tok), free_export(data->env_export),
			exit(127));
	// if (access(data->cmd[0], F_OK) == 0)
	// {
	// 	if (access(data->cmd[0], R_OK | W_OK | X_OK) == 0)
	// 		return (ft_printf("%s: Permission denied\n", data->cmd[0]), free_tab(data->cmd), free_export(data->env_export), exit(126));
	// 	else
	// 		return (ft_printf("%s: Is a directory\n", data->cmd[0]), free_tab(data->cmd), free_tok(tok), free_export(data->env_export), exit(126));
	// }
	tab = ft_envp_copy_to_tab(data);
	if (path)
		execve(path, data->cmd, tab);
	return (free_tab(data->cmd), free(path), free_tok(tok),
		free_export(data->env_export), exit(0));
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
	int			i;
	t_heredoc	*here_docs;

	here_docs = here_doc_launch(data, tok);
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
	i = 0;
	while (i < data->nb_hd)
	{
		close(here_docs[i].fd[0]);
		i++;
	}
	free(here_docs);
	close(data->pipe_fd[0]);
	return (0);
}
