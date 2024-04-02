/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:04:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/02 04:10:56 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void here_doc_loop(t_data *data, char *lim, int *pipe)
{
    char *buf;
    int i;

    i = 0;
    close(pipe[0]);
    while (1)
    {
        buf = readline("> ");
        if (!buf || !ft_strcmp(buf, lim))
            break;
        ft_putstr_fd(buf, pipe[1]);
    }
    ft_putstr_fd(NULL, pipe[1]);
    close(pipe[1]);
    close(data->curr_here_doc);
    exit(0  );
}

void init_heredoc(t_data *data, t_heredoc **here_docs, char *lim, int i)
{
    int pid;
    int pipes[2];

    if(pipe(pipes) < 0)
        return ;
    ft_stock_here_doc(here_docs, ft_lstnew_here_doc(pipes[0], lim, i));
    pid = fork();
    if (!pid)
    {
        data->curr_here_doc = pipes[1];
        here_doc_loop(data, lim, pipes);
    }
    wait(NULL);
    close(pipes[1]);
}

t_heredoc    *exec_here_docs(t_data *data, t_token **tok)
{
    t_token *tmp;
    t_heredoc *here_docs;
    int i;


    i = 0;
    tmp = *tok;
    here_docs = NULL;
    while (tmp)
    {
        if (tmp->type == PIPE)
            i++;
        if (tmp->type == DLESS)
        {
            init_heredoc(data, &here_docs, tmp->next->str, i);
        }
        tmp = tmp->next;
    }
    return (here_docs);
}
void close_here_docs(t_heredoc *h_docs, int size)
{
	int i;
	
	i = 0;
	while (i < size)
	{
		close(h_docs->fd);
        free(h_docs->lim);
        i++;
	}
	if (size)
		free(h_docs);
	
}

int	find_heredoc(t_heredoc *h_docs, int size, t_token *tok)
{
	int i;

	i = -1;
	while (++i < size)
	{
		if (!ft_strcmp(tok->next->str, h_docs->lim))
			return (h_docs->fd);
	}
	return(-1);
}