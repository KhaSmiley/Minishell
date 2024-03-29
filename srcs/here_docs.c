/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:04:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/29 04:10:23 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_heredoc *ft_lstlast_here_doc(t_heredoc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_heredoc	*ft_lstnew_here_doc(int fd, char *content, int nb_cmd)
{
	t_heredoc	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
    new->fd = fd;
	new->lim = content;
    new->in_cmd = nb_cmd;
	new->next = NULL;
	return (new);
}

void	ft_stock_here_doc(t_heredoc **lst, t_heredoc *new_link)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new_link;
	else
		(ft_lstlast_here_doc(*lst))->next = new_link;
}
void print_list_here_doc(t_heredoc *lst)
{
    if (!lst)
		return ;
    while(lst)
    {
        printf("string: %s\nin_cmd = %d\n", lst->lim, lst->in_cmd);
        lst = lst->next;
    }
    return ;
}

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
    exit(0);
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
