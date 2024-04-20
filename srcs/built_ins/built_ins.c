/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/09 16:35:49 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	to_builtin_or_not_to_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	lets_builtin_no_fork(t_data *data, char **cmd, t_token **tok)
{
	if (!cmd[0])
		return (0);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (ft_pwd(data), 1);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return (ft_cd(cmd, data), 1);
	else if (!ft_strncmp(cmd[0], "env", 3))
		return (ft_env(data), 1);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return (ft_echo(cmd), 1);
	else if (!ft_strncmp(cmd[0], "export", 6))
		return (ft_export(data, cmd), 1);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(data, cmd), 1);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		return (ft_exit_no_fork(cmd, data, tok), 1);
	return (0);
}

int	lets_builtin(t_data *data, char **cmd, t_token **tok)
{
	if (!cmd[0])
		return (0);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (ft_pwd(data), 1);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return (ft_cd(cmd, data), 1);
	else if (!ft_strncmp(cmd[0], "env", 3))
		return (ft_env(data), 1);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return (ft_echo(cmd), 1);
	else if (!ft_strncmp(cmd[0], "export", 6))
		return (ft_export(data, cmd), 1);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(data, cmd), 1);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		return (ft_exit_fork(cmd, data, tok), 1);
	return (0);
}

int	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		data->status = 1;
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

int	ft_cd(char **cmd, t_data *data)
{
	int		ret;
	char	*path;

	if (!check_cd_args(data, cmd))
		return (0);
	if (!cmd[1])
	{
		path = get_home_env(data->env_export);
		if (!path)
		{
			data->status = 1;
			return (0);
		}
	}
	else
		path = cmd[1];
	ret = chdir(path);
	if (ret == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", cmd[1]);
		data->status = 1;
		return (0);
	}
	return (1);
}
