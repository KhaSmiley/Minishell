/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:59:29 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/11 15:08:47 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_hdocs(char *lim, int pipe, t_data *data)
{
	char	*line;
	int		i;

	i = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(E F, data->minishell_line_no, lim);
			break ;
		}
		if (!ft_strcmp(line, lim))
			break ;
		ft_putstr_newline_fd(line, pipe);
		free(line);
		i++;
	}
	close(pipe);
}

void	exec_hdocs(t_heredoc *h_docs, t_data *data, int *i, t_token **tok)
{
	signal(SIGINT, &sigint_hd);
	while (*i < data->nb_hd)
	{
		close(h_docs[*i].fd[0]);
		write_hdocs(h_docs[*i].lim, h_docs[*i].fd[1], data);
		(*i)++;
	}
	if (data->flag_hd == 1)
	{
		dup2(data->std_fd[0], STDIN_FILENO);
		dup2(data->std_fd[1], STDOUT_FILENO);
		close(data->std_fd[0]);
		close(data->std_fd[1]);
		free_tab(data->builtin);
	}
	free(h_docs);
	free_export(data->env_export);
	free_tok(tok);
	exit(0);
}

void	close_heredocs(t_data *data, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		close(data->here_docs[i].fd[0]);
		i++;
	}
	if (limit)
		free(data->here_docs);
}

int	find_heredoc(t_data *data, t_token *tmp)
{
	int	i;

	i = -1;
	while (++i < data->nb_hd)
	{
		if (!ft_strcmp(data->here_docs[i].lim, tmp->next->str))
			return (data->here_docs[i].fd[0]);
	}
	return (-1);
}

void	here_doc_launch(t_data *data, t_token **tok)
{
	int			i;
	int			pid;

	i = 0;
	if (data->nb_hd == 0)
		return ;
	data->here_docs = ft_calloc(sizeof(t_heredoc), data->nb_hd);
	if (!data->here_docs)
		return ;
	init_here_doc(data->here_docs, tok, data);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_hdocs(data->here_docs, data, &i, tok);
	else if (pid > 0)
	{
		while (i < data->nb_hd)
			close(data->here_docs[i++].fd[1]);
	}
	signal(SIGINT, &sigint_handler);
	waitpid(pid, 0, 0);
}
