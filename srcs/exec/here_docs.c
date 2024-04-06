/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:59:29 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/05 17:28:36 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_nb_hdoc(t_token *tok, t_data *data)
{
	t_token	*tmp;

	data->nb_hd = 0;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == DLESS)
		{
			data->nb_hd++;
		}
		tmp = tmp->next;
	}
}

void	init_here_doc(t_heredoc *h_docs, t_token **tok, t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = *tok;
	i = 0;
	while (i < data->nb_hd)
	{
		if (tmp->type == DLESS)
		{
			h_docs[i].in_cmd = i;
			h_docs[i].lim = tmp->next->str;
			pipe(h_docs[i].fd);
			i++;
		}
		tmp = tmp->next;
	}
}

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
			ft_printf("warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", data->minishell_line_no, lim);
			break;
		}
		if (!ft_strcmp(line, lim))
			break ;
		ft_putstr_fd(line, pipe);
		free(line);
		i++;
	}
	close(pipe);
}

void	exec_hdocs(t_heredoc *h_docs, t_data *data, int *i, t_token **tok)
{
	while (*i < data->nb_hd)
	{
		close(h_docs[*i].fd[0]);
		write_hdocs(h_docs[*i].lim, h_docs[*i].fd[1], data);
		(*i)++;
	}
	// ft_printf("HERE\n");
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
	int i;
	t_heredoc *h_docs;
	int pid;

	i = 0;
	data->nb_hd = 0;
	find_nb_hdoc(*tok, data);
	if (data->nb_hd == 0)
		return (NULL);
	h_docs = ft_calloc(sizeof(t_heredoc), data->nb_hd);
	if (!h_docs)
		return (NULL);
	init_here_doc(h_docs, tok, data);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	i = 0;
	if (pid == 0)
	{
		signal(SIGINT, &sigint_hd);
		exec_hdocs(h_docs, data, &i, tok);
	}
	else if (pid > 0)
	{
		while (i < data->nb_hd)
		{
			// ft_printf("close h_docs\n");
			close(h_docs[i++].fd[1]);
		}
	}
	waitpid(pid, 0, 0);
	signal(SIGINT, &sigint_handler);
	return (h_docs);
}
