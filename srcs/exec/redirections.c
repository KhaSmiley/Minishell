/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:35:59 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/03 20:37:17 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	file_error(t_token *tok, t_data *data, char *str)
{
	fprintf(stderr, "%s: No such file or directory\n", str);
	free_tok(&tok);
	if (data->builtin)
		free_tab(data->builtin);
	if (data->cmd)
		free_tab(data->cmd);
	close_fds(data);
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
			file_error(tok, data, tmp->next->str);
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
