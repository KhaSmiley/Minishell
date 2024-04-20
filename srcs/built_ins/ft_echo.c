/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:05:04 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/11 14:31:15 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	num_args;
	int	no_line;

	i = 1;
	num_args = 1;
	no_line = check_echo_option(cmd, 0, 0);
	if (!cmd[i] && !no_line)
	{
		printf("\n");
		return (1);
	}
	while (cmd[num_args])
		num_args++;
	i = no_line + 1;
	echo_print(cmd, i, num_args);
	if (!no_line)
		printf("\n");
	return (1);
}

void	echo_print(char **cmd, int i, int num_args)
{
	int	j;
	int	printed;

	printed = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] != '\\')
				printed = printf("%c", cmd[i][j]);
			j++;
		}
		if (i < num_args - 1)
			printf(" ");
		i++;
	}
}

int	check_echo_option(char **args, int i, int j)
{
	if (!args[1] || ft_strncmp(args[1], "-n", 2) != 0)
		return (0);
	while (args[++i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '-')
				j++;
			if (args[i][j] != 'n')
				return (i - 1);
			if (args[i][j + 1] != 'n' && args[i][j + 1] != '\0' && (args[i][j
					+ 1] != ' ' || args[i][j + 1] != '\t'))
				return (i - 1);
			while (args[i][j] == 'n')
			{
				if (args[i][j] == '\0')
					break ;
				j++;
			}
			if (args[i][j] != 'n' && args[i][j] != '\0')
				return (i - 1);
		}
	}
	return (i - 1);
}
