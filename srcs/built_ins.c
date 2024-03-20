/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/20 19:38:10 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	to_builtin_or_not_to_builtin(char **cmd)
{
	printf("in built ins cmd[0] = %s\n", cmd[0]);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return(ft_pwd(), 1);
	if (!ft_strncmp(cmd[0], "cd", 2))
		return(ft_cd(cmd, NULL), 1);
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
	(void)envp_cpy;

	printf("in ft_cd\n");
	printf("cmd[0] = %s\n", cmd[0]);
	printf("cmd[1] = %s\n", cmd[1]);

	//no args go to HOME - find HOME in envp_cpy and send to chdir
	//create find_str_in_envp_cpy func
	// if (!cmd[1])
	// {
	// 	//find HOME in envp_cpy and stock in cmd[0]
	// }
	//check 1 arg (if not error) ?
	ret = chdir(cmd[1]);
	printf("ret = %d\n", ret);
	if (ret == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd[1]);
		return (0);
	}
	return (1);
}
