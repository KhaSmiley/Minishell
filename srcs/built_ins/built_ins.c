/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/31 01:52:20 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lets_builtin(t_data *data, char **cmd, char **envp_cpy)
{
	if (!cmd[0])
		return (0);
	//printf("lets builtin = %s\n", cmd[0]);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return(ft_pwd(), 1);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return(ft_cd(cmd, envp_cpy), 1);
	else if (!ft_strncmp(cmd[0], "env", 3))
		return(ft_env(data), 1);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return(ft_echo(cmd), 1);
	else if (!ft_strncmp(cmd[0], "export", 6))
		return(ft_export(data, cmd) , 1);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return(ft_unset(data, cmd) ,1);
	return (0);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("getcwd error\n");
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

int	ft_cd(char **cmd, char **envp_cpy)
{
	int		ret;
	char	*path;

	if (cmd[1] == NULL)
	{
		path = get_home_env(envp_cpy);
		if (!path)
			return (printf("cd no args, HOME not found\n"), 0);
	}
	else
		path = cmd[1];
	ret = chdir(path);
	if (ret == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd[1]);
		return (0);
	}
	return (1);
}

int	ft_env(t_data *data)
{
	ft_envp_copy_export(data);
	print_list_export(data->env_export);
	return (1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	num_args;
	int	no_line;

	i = 1;
	num_args = 1;
	no_line = check_echo_option(cmd);
	//printf("no line count: %d\n", no_line);
	if (!cmd[i] && !no_line)
	{
		printf("\n");
		return (1);
	}
	while (cmd[num_args])
		num_args++;
	i = no_line + 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (i < num_args - 1)
			printf(" ");
		i++;
	}
	if (!no_line)
		printf("\n");
	return (1);
}
