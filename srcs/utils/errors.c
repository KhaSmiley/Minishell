/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:54:08 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/08 18:54:15 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_errors(char **args)
{
	struct stat	path_stat;

	stat(args[0], &path_stat);
	if (!access(args[0], F_OK) && access(args[0], X_OK))
	{
		return (ft_printf("minishell: %s: %s\n", args[0], strerror(errno)),
			126);
	}
	else if ((!ft_strncmp(args[0], "./", 2) || ft_get_last_char(args[0]) == '/')
		&& access(args[0], F_OK))
	{
		return (ft_printf("minishell: %s: %s\n", args[0], strerror(errno)),
			127);
	}
	else if (!access(args[0], F_OK) && (!ft_strncmp(args[0], "./", 2)
			&& S_ISDIR(path_stat.st_mode)))
	{
		return (ft_printf("minishell: %s: %s\n", args[0], "Is a directory"),
			126);
	}
	else if (ft_strncmp(args[0], "./", 2))
		return (ft_printf("minishell: %s: %s\n", args[0], "command not found"),
			127);
	return (0);
}
