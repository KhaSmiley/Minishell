/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:58:11 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/10 21:29:09 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit_atoi(char *str)
{
	size_t	i;
	int		sign;

	sign = 1;
	i = 0;
	if (*str == '-')
	{
		sign = -sign;
		++str;
	}
	else if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + *str - '0';
		if ((i > LONG_MAX && sign == 1) || (i - 1 > LONG_MAX && sign == -1))
			return (0);
		++str;
	}
	if (*str)
		return (0);
	return (1);
}

void	ft_free_exit_no_fork(t_data *data, t_token **tok)
{
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	free_tok(tok);
}

void	clear_exit(t_data *data, char **args, t_token **tok, int i)
{
	if (i == 0)
	{
		close(data->std_fd[0]);
		close(data->std_fd[1]);
	}
	if (i == 2)
	{
		free_export(data->env_export);
		free_tab(args);
		free_tok(tok);
		exit(data->status);
	}
	free_export(data->env_export);
	free_tab(args);
	free_tok(tok);
}

int	ft_find_nb_args_exit(t_token **tok)
{
	int		i;
	t_token	*tmp;

	tmp = *tok;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i - 1);
}
