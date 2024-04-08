/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:03:23 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 18:58:39 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_atoi_exit(t_data *data, char **args, t_token **tok)
{
	if (!ft_exit_atoi(args[1]))
	{
		ft_printf("exit : %s: numeric argument required\n", args[1]);
		clear_exit_no_fork(data, args, tok, 0);
		exit(2);
	}
}

int	ft_exit_fork(char **args, t_data *data, t_token **tok)
{
	if (!args || !*args)
	{
		free_export(data->env_export);
		free_tok(tok);
		exit(g_sig_return);
	}
	if (args[0] && args[1])
		ft_check_atoi_exit(data, args, tok);
	if (args[1] && args[2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	if (args[1])
	{
		data->status = ft_atoi(args[1]);
		clear_exit_no_fork(data, args, tok, 2);
	}
	clear_exit_no_fork(data, args, tok, 1);
	exit(0);
}

int	ft_exit_no_fork(char **args, t_data *data, t_token **tok)
{
	int		i;

	printf("exit\n");
	if (!args || !*args)
	{
		ft_free_exit_no_fork(data, tok);
		exit(g_sig_return);
	}
	i = ft_find_nb_args_exit(tok);
	if (i == 2)
		ft_check_atoi_exit(data, args, tok);
	if (i > 2)
	{
		data->status = 1;
		return (ft_printf("exit: too many arguments\n"), 1);
	}
	if (i == 2)
		data->status = ft_atoi(args[1]);
	clear_exit_no_fork(data, args, tok, 0);
	exit(data->status);
}
