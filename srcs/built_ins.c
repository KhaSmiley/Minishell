/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/29 01:11:39 by kboulkri         ###   ########.fr       */
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
	lets_builtin(data, builtin, data->envp_cpy);
	if (ft_strcmp(builtin[0], "unset") == 0)
		return (free(builtin[0]), 0);
	free_tab(builtin);
	return (0);
}

int	to_builtin_or_not_to_builtin(char *cmd)
{
	//printf("checking if cmd[0] is builtin = %s\n", cmd);
	if (!ft_strcmp(cmd, "pwd"))
		return(1);
	else if (!ft_strcmp(cmd, "cd"))
		return(1);
	else if (!ft_strcmp(cmd, "env"))
		return(1);
	else if (!ft_strcmp(cmd, "echo"))
		return(1);
	else if (!ft_strcmp(cmd, "export"))
		return(1);
	else if (!ft_strcmp(cmd, "unset"))
		return(1);
	return (0);
}

int	lets_builtin(t_data *data, char **cmd, char **envp_cpy)
{
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
		return(ft_export(data, cmd) ,1);
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
	print_list_export(data->env_export);
	return (1);
}

int	check_echo_option(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		//printf("args[%d] = %s\n", i, args[i]);
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '-')
				j++;
			if (args[i][j] != 'n')
				return (i - 1);
			if (args[i][j + 1] != 'n' && args[i][j + 1] != '\0' && (args[i][j + 1] != ' ' || args[i][j + 1] != '\t'))
				return (i - 1);
			while (args[i][j] == 'n')
			{
				if (args[i][j] != 'n' && args[i][j] != '\0')
					return (i - 1);
				else if (args[i][j] == '\0')
					break ;
				j++;
			}
		}
		i++;
	}
	return (i - 1);
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
