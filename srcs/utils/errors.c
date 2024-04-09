/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:54:08 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/09 03:55:24 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_errors(char **args)
{
	struct stat	path_stat;

	stat(args[0], &path_stat);
	if ((!ft_strncmp(args[0], "./", 2) || !ft_strncmp(args[0], "../",
				3) || ft_strchr(args[0], '/'))
		&& access(args[0], F_OK))
		return (ft_printf(" minishell: %s: %s\n", args[0],
				strerror(errno)), 127);
	else if ((!ft_strncmp(args[0], "./", 2) || !ft_strncmp(args[0],
				"../", 3) || ft_strchr(args[0], '/'))
		&& S_ISDIR(path_stat.st_mode))
		return (ft_printf("minishell: %s: Is a directory\n", args[0]),
			126);
	else if (!access(args[0], F_OK) && ft_strchr(args[0], '/')
		&& S_ISDIR(path_stat.st_mode))
		return (ft_printf("minishell: %s: Is a directory\n", args[0]),
			126);
	else if ((!ft_strncmp(args[0], "./", 2) || !ft_strncmp(args[0],
				"../", 3) || ft_strchr(args[0], '/'))
		&& access(args[0], X_OK))
		return (ft_printf("minishell: %s: %s\n", args[0],
				strerror(errno)), 126);
	return (ft_printf("minishell: %s: command not found\n", args[0]),
		127);
}
