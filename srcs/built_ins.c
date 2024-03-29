/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/29 01:03:52 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	to_builtin_or_not_to_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	//printf("checking if cmd[0] is builtin = %s\n", cmd);
	if (!ft_strncmp(cmd, "pwd", 3))
		return(1);
	else if (!ft_strncmp(cmd, "cd", 2))
		return(1);
	else if (!ft_strncmp(cmd, "env", 3))
		return(1);
	else if (!ft_strncmp(cmd, "echo", 4))
		return(1);
	// else if (!ft_strncmp(cmd, "export", 6))
	// 	return(1);
	// else if (!ft_strncmp(cmd, "unset", 5))
	// 	return(1);
	else if (!ft_strncmp(cmd, "exit", 4))
		return(1);
	return (0);
}

int	lets_builtin(char **cmd, char **envp_cpy, t_token **tok)
{
	if (!cmd[0])
		return (0);
	//printf("lets builtin = %s\n", cmd[0]);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return(ft_pwd(), 1);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return(ft_cd(cmd, envp_cpy), 1);
	else if (!ft_strncmp(cmd[0], "env", 3))
		return(ft_env(envp_cpy), 1);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return(ft_echo(cmd), 1);
	// else if (!ft_strncmp(cmd[0], "export", 6))
	// 	return(ft_export(cmd, envp_cpy), 1);
	// else if (!ft_strncmp(cmd[0], "unset", 5))
	// 	return(ft_unset(cmd, envp_cpy), 1);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		return(ft_exit(cmd, envp_cpy, tok), 1);
	return (0);
}

void	ft_exit(char **cmd, char **envp_cpy, t_token **tok)
{
	free_tab(envp_cpy);
	free_tab(cmd);
	free_tok(tok);
	rl_clear_history();
	exit(0);
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

int	ft_env(char **envp_cpy)
{
	print_tab(envp_cpy);
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
