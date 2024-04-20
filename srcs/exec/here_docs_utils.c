/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:57:22 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/09 07:44:13 by kboulkri         ###   ########.fr       */
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

void	ft_close_hd_child(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_hd)
	{
		close(data->here_docs[i].fd[0]);
		i++;
	}
	if (data->nb_hd)
		free(data->here_docs);
}

void	ft_putstr_newline_fd(char *str, int pipe)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		write(pipe, &str[i], 1);
		i++;
	}
	write(pipe, "\n", 1);
}
