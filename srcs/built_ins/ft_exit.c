/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:03:23 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 05:38:46 by kboulkri         ###   ########.fr       */
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

int	ft_exit_fork(char **args, t_data *data, t_token **tok)
{
	int	exit_value;

	if (!args || !*args)
	{
		free_export(data->env_export);
		free_tok(tok);
		exit(g_sig_return);
	}
	if (args[0] && args[1])
	{
		if (!ft_exit_atoi(args[1]))
		{
			ft_printf("exit : %s: numeric argument required\n", args[1]);
			clear_exit_no_fork(data, args, tok, 1);
			exit(2);
		}
	}
	if (args[1] && args[2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	exit_value = ft_atoi(args[1]);
	clear_exit_no_fork(data, args, tok, 1);
	exit(exit_value);
}

int	ft_exit_no_fork(char **args, t_data *data, t_token **tok)
{
	int		i;
	int		exit_value;
	t_token	*tmp;

	i = 0;
	tmp = *tok;
	exit_value = 0;
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
		exit_value = ft_atoi(args[1]);
	clear_exit_no_fork(data, args, tok, 0);
	exit(exit_value);
}
