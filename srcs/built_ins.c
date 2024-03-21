/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/21 15:01:58 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	to_builtin_or_not_to_builtin(char **cmd)
{
	printf("checking if cmd[0] is builtin = %s\n", cmd[0]);

	if (!ft_strncmp(cmd[0], "pwd", 3))
		return(1);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return(1);
	return (0);
}

int	lets_builtin(char **cmd, char **envp_cpy)
{
	printf("lets builtin = %s\n", cmd[0]);

	if (!ft_strncmp(cmd[0], "pwd", 3))
		return(ft_pwd(), 1);
	if (!ft_strncmp(cmd[0], "cd", 2))
		return(ft_cd(cmd, envp_cpy), 1);

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

char	*get_home_env(char **envp_cpy)
{
	int		i;

	i = 0;
	while (envp_cpy[i])
	{
		if (!ft_strncmp(envp_cpy[i], "HOME=", 5))
			return (envp_cpy[i] + 5);
		i++;
	}
	return (NULL);
}

int	ft_cd(char **cmd, char **envp_cpy)
{
	int		ret;
	char	*path;
	printf("in ft_cd\n");
	printf("cmd[0] = %s\n", cmd[0]);
	printf("cmd[1] = %s\n", cmd[1]);

	//check 1 arg (if not error) ?

	//no args go to HOME - find HOME in envp_cpy and send to chdir
	//create find_str_in_envp_cpy func
	if (cmd[1] == NULL)
	{
		path = get_home_env(envp_cpy);
		printf("hom path returned %s\n", path);
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (0);
		}
		//printf("home found %s\n", path);
	}
	else
		path = cmd[1];
	ret = chdir(path);
	printf("ret = %d\n", ret);
	if (ret == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd[1]);
		return (0);
	}
	return (1);
}
