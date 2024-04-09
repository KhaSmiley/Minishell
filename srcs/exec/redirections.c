/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:35:59 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/09 01:50:48 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	file_error(t_token *tok, t_data *data, char *str)
{
	(void)tok;
	if (access(str, F_OK) == 0)
	{
		fprintf(stderr, "%s: Permission denied\n", str);
		data->status = 1;
	}
	else
	{
		fprintf(stderr, "%s: No such file or directory\n", str);
		data->status = 1;
	}
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

int	ft_dup2_in_redir_files(int fd, t_token *tmp, t_token *tok, t_data *data)
{
	if (fd == -1)
	{
		file_error(tok, data, tmp->next->str);
		return (0);
	}
	if (tmp->type == GREATER || tmp->type == DGREATER)
		dup2(fd, STDOUT_FILENO);
	else if (tmp->type == LESS || tmp->type == DLESS)
		dup2(fd, STDIN_FILENO);
	if (tmp->type != DLESS)
		close(fd);
	return (1);
}

int	redir_files(t_token *tok, int i, t_data *data)
{
	int		fd;
	t_token	*tmp_curr;

	tmp_curr = find_curr_tok_pipe(&tok, i);
	while (tmp_curr && tmp_curr->type != PIPE)
	{
		if (tmp_curr->type == WORD)
		{
			tmp_curr = tmp_curr->next;
			continue ;
		}
		if (tmp_curr->type == GREATER)
			fd = open(tmp_curr->next->str, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (tmp_curr->type == DGREATER)
			fd = open(tmp_curr->next->str, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (tmp_curr->type == LESS)
			fd = open(tmp_curr->next->str, O_RDONLY);
		else if (tmp_curr->type == DLESS)
			fd = find_heredoc(data, tmp_curr);
		if (!ft_dup2_in_redir_files(fd, tmp_curr, tok, data))
			return (0);
		tmp_curr = tmp_curr->next;
	}
	close_heredocs(data, data->nb_hd);
	return (1);
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
