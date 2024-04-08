/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils_third.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:24:59 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 05:12:41 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_exit_no_fork(t_data *data, char **args, t_token **tok, int i)
{
	if (i == 0)
	{
		close(data->std_fd[0]);
		close(data->std_fd[1]);
	}
	free_export(data->env_export);
	free_tab(args);
	free_tok(tok);
}

void	ft_free_exit_no_fork(t_data *data, t_token **tok)
{
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	free_export(data->env_export);
	free_tok(tok);
}

void	ft_free_in_export_func(t_export *tmp, char *key)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	free(key);
}
