/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 06:46:44 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_errors(char **args)
{
	struct stat	path_stat;

	stat(args[0], &path_stat);
	if (!access(args[0], F_OK) && access(args[0], X_OK))
	{
		return (ft_printf("minishell: %s: %s\n", args[0], strerror(errno)),
			126);
	}
	else if ((!ft_strncmp(args[0], "./", 2) || ft_get_last_char(args[0]) == '/')
		&& access(args[0], F_OK))
	{
		return (ft_printf("minishell: %s: %s\n", args[0], strerror(errno)),
			127);
	}
	else if (!access(args[0], F_OK) && (!ft_strncmp(args[0], "./", 2)
			&& S_ISDIR(path_stat.st_mode)))
	{
		return (ft_printf("minishell: %s: %s\n", args[0], "Is a directory"),
			126);
	}
	else if (ft_strncmp(args[0], "./", 2))
		return (ft_printf("minishell: %s: %s\n", args[0], "command not found"),
			127);
	return (0);
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
	if (to_builtin_or_not_to_builtin(data->cmd[0]))
	{
		lets_builtin(data, data->cmd, tok);
		// if builtin is last cmd and it fails data->status = 1
		// in all other cases data->status = 0
		return (free_tab(data->cmd), free_tok(tok),
			free_export(data->env_export), exit(0));
	}
	path = complete_path(data, data->cmd[0]);
	// if (!path)
	// 	return (ft_printf("minishell: %s: command not found\n", data->cmd[0]),
	// 		free_tab(data->cmd), free_tok(tok), free_export(data->env_export),
	// 		exit(127));
	tab = ft_envp_copy_to_tab(data);
	if (path)
		execve(path, data->cmd, tab);
	data->status = ft_handle_errors(data->cmd);
	free(path);
	path = NULL;
	free_tab(data->cmd);
	free_tok(tok);
	free_tab(tab);
	free_export(data->env_export);
	exit(data->status);
	// if (!path)
	// 	return (ft_printf("minishell: %s: command not found\n", data->cmd[0]),
	// 		free_tab(data->cmd), free_tok(tok), free_export(data->env_export),
	// 		exit(127));
	// if (!data->cmd)
	// 	return (free_tok(tok), free(data->input), free_export(data->env_export),
	// 		exit(0));
	// if (!data->cmd[0])
	// 	return (ft_printf("minishell: : command not found\n"),
	// 		free_tab(data->cmd), free_tok(tok), free_export(data->env_export),
	// 		exit(127));
	// return (free(path), free_tok(tok),
	// 	free_export(data->env_export), exit(0));
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
