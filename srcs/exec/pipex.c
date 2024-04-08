/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 20:09:20 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	end_child_process(char *path, t_data *data, t_token **tok, char **tab)
{
	free(path);
	path = NULL;
	free_tab(data->cmd);
	free_tok(tok);
	free_tab(tab);
	free_export(data->env_export);
}

void	child_process(t_data *data, t_token **tok, t_heredoc *h_docs, int i)
{
	char	*path;
	char	**tab;

	(void)h_docs;
	default_signals();
	data->cmd = tok_to_tab(tok, i);
	redirection(data, i);
	if (!redir_files(*tok, i, h_docs, data))
		return (free_export(data->env_export), free_tok(tok),
			free_tab(data->cmd), exit(1));
	if (!data->cmd)
		return (free_tok(tok), free_tab(data->cmd),
			free_export(data->env_export), exit(0));
	built_ins(data, tok);
	path = complete_path(data, data->cmd[0]);
	tab = ft_envp_copy_to_tab(data);
	if (path)
		execve(path, data->cmd, tab);
	data->status = ft_handle_errors(data->cmd);
	end_child_process(path, data, tok, tab);
	exit(data->status);
}

void	parent_process(t_data *data, int i)
{
	close(data->pipe_fd[1]);
	if (i != 0)
		close(data->tmp_fd);
	data->tmp_fd = data->pipe_fd[0];
}

void	ft_waitpid_child(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		waitpid(data->pid[i++], &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		else if (WIFSIGNALED(data->status) && WTERMSIG(data->status) == SIGQUIT)
		{
			ft_printf("Quit (core dumped)\n");
			g_sig_return = 131;
		}
	}
}

int	exec_pipe(t_data *data, t_token **tok)
{
	int			i;
	t_heredoc	*here_docs;

	here_docs = here_doc_launch(data, tok);
	i = -1;
	disable_signals();
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
	ft_waitpid_child(data);
	ft_close_hd_child(data, here_docs);
	close(data->pipe_fd[0]);
	return (0);
}
