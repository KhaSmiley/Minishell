/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/21 19:57:21 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_first_cmd(t_token **tok)
{
	t_token *tmp;

	tmp = *tok;
	while (tmp)
	{
		if (tmp->type == WORD)
			return (tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}

int	one_built_in(char **builtin, t_data *data)
{
	// int i = 0;
	// while (builtin[i])
	// {
	// 	printf("one builtin cmd[%d] = %s\n", i, builtin[i]);
	// 	i++;
	// }
	lets_builtin(builtin, data->envp_cpy);
	free_tab(builtin);
	return (0);
}

int	to_builtin_or_not_to_builtin(char *cmd)
{
	//printf("checking if cmd[0] is builtin = %s\n", cmd);
	if (!ft_strncmp(cmd, "pwd", 3))
		return(1);
	else if (!ft_strncmp(cmd, "cd", 2))
		return(1);
	else if (!ft_strncmp(cmd, "env", 3))
		return(1);
	else if (!ft_strncmp(cmd, "echo", 4))
		return(1);
	return (0);
}

int	lets_builtin(char **cmd, char **envp_cpy)
{
	//printf("lets builtin = %s\n", cmd[0]);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return(ft_pwd(), 1);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return(ft_cd(cmd, envp_cpy), 1);
	else if (!ft_strncmp(cmd[0], "env", 3))
		return(ft_env(envp_cpy), 1);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return(ft_echo(cmd), 1);
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

	if (cmd[1] == NULL)
	{
		path = get_home_env(envp_cpy);
		if (!path)
			return (printf("cd noa args, HOME not found\n"), 0);
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

int	ft_env(char **envp_cpy)
{
	print_tab(envp_cpy);
	return (1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	num_args;

	i = 1;
	num_args = 0;
	while (cmd[num_args])
		num_args++;
	if (!cmd[i])
	{
		printf("\n");
		return (1);
	}
	// to do: check cmd[2++] for -n
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (i < num_args)
			printf(" ");
		i++;
	}
	printf("\n");
	return (1);
}
