/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:59:29 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 07:04:25 by kboulkri         ###   ########.fr       */
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
	free(h_docs);
	free_export(data->env_export);
	free_tok(tok);
	exit(0);
}

void	close_heredocs(t_heredoc *h_docs, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		close(h_docs[i].fd[0]);
		i++;
	}
	if (limit)
		free(h_docs);
}

int	find_heredoc(t_heredoc *h_docs, t_data *data, t_token *tmp)
{
	int	i;

	i = -1;
	while (++i < data->nb_hd)
	{
		if (!ft_strcmp(h_docs[i].lim, tmp->next->str))
			return (h_docs[i].fd[0]);
	}
	return (-1);
}

t_heredoc	*here_doc_launch(t_data *data, t_token **tok)
{
	int			i;
	t_heredoc	*h_docs;
	int			pid;

	i = 0;
	if (data->nb_hd == 0)
		return (NULL);
	h_docs = ft_calloc(sizeof(t_heredoc), data->nb_hd);
	if (!h_docs)
		return (NULL);
	init_here_doc(h_docs, tok, data);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_hdocs(h_docs, data, &i, tok);
	else if (pid > 0)
	{
		while (i < data->nb_hd)
			close(h_docs[i++].fd[1]);
	}
	waitpid(pid, 0, 0);
	signal(SIGINT, &sigint_handler);
	return (h_docs);
}
