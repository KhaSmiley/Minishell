/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 03:45:20 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/09 07:42:40 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// if builtin is last cmd and it fails data->status = 1
// in all other cases data->status = 0
void	built_ins(t_data *data, t_token **tok)
{
	if (to_builtin_or_not_to_builtin(data->cmd[0]))
	{
		lets_builtin(data, data->cmd, tok);
		return (free_tab(data->cmd), free_tok(tok),
			free_export(data->env_export), exit(0));
	}
}

int	one_built_in(char **builtin, t_token **tok, t_data *data)
{
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	data->builtin = builtin;
	here_doc_launch(data, tok);
	if (!redir_files(*tok, 0, data))
	{
		dup2(data->std_fd[0], STDIN_FILENO);
		dup2(data->std_fd[1], STDOUT_FILENO);
		close(data->std_fd[0]);
		close(data->std_fd[1]);
		return (0);
	}
	lets_builtin_no_fork(data, builtin, tok);
	free_tab(builtin);
	free_tok(tok);
	dup2(data->std_fd[0], STDIN_FILENO);
	dup2(data->std_fd[1], STDOUT_FILENO);
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	return (1);
}

char	*find_first_cmd(t_token **tok)
{
	t_token	*tmp;

	tmp = *tok;
	while (tmp)
	{
		if (tmp->type == WORD)
			return (tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_digits(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_isdigit(args[i]) || i > 18)
			return (0);
		i++;
	}
	return (1);
}
