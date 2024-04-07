/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/07 06:26:37 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lets_builtin_no_fork(t_data *data, char **cmd, t_token **tok)
{
	if (!cmd[0])
		return (0);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (ft_pwd(), 1);
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
		return (ft_pwd(), 1);
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

int	ft_cd(char **cmd, t_data *data)
{
	int		ret;
	char	*path;

	if (cmd[1] == NULL)
	{
		path = get_home_env(data->env_export);
		if (!path)
			return (ft_printf("cd no args, HOME not found\n"), 0);
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
	if (cmd[2])
	{
		ft_printf("cd : too many arguments");
		data->status = 1;
		return (0);
	}
	return (1);
}

int	ft_env(t_data *data)
{
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
	no_line = check_echo_option(cmd, 0, 0);
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

int	check_digits(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_isdigit(args[i]) || i > 18)
			return (0);
		i++;
	}
	return (1);
}

int ft_exit_atoi(char *str)
{
	size_t i;
	int sign;

	sign = 1;
	i = 0;
	if (*str == '-')
	{
		sign = -sign;
		++str;
	}
	else if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + *str - '0';
		if ((i > LONG_MAX && sign == 1) || (i - 1 > LONG_MAX && sign == -1))
			return (0);
		++str;
	}
	if (*str)
		return (0);
	return (1);
}

void ft_free_exit_no_fork(t_data *data, t_token **tok)
{
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	free_export(data->env_export);
	free_tok(tok);

}

int	ft_exit_no_fork(char **args, t_data *data, t_token **tok)
{
	int	i;
	int	exit_value;
	t_token *tmp;

	i = 0;
	tmp = *tok;
	exit_value = 0;
	printf("exit\n");
	if (!args || !*args)
	{
		ft_free_exit_no_fork(data, tok);
		exit(g_sig_return);
	}
	while(tmp)
	{
		if(tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	if (i == 2)
	{
		if (!ft_exit_atoi(args[1]))
		{
			ft_printf("exit : %s: numeric argument required\n", args[1]);
			clear_exit_no_fork(data, args, tok);
			exit(2);
		}
	}
	if (i > 2)
	{
		data->status = 1;
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	if (i == 2)
		exit_value = ft_atoi(args[1]);
	clear_exit_no_fork(data, args, tok);
	exit(exit_value);
}

void clear_exit_no_fork(t_data *data, char **args, t_token **tok)
{
	close(data->std_fd[1]);
	close(data->std_fd[0]);
	free_export(data->env_export);
	free_tab(args);
	free_tok(tok);
}

int	ft_exit_fork(char **args, t_data *data, t_token **tok)
{
	int	i;
	int	exit_value;

	i = 0;
	if (!args || !*args)
	{
		free_export(data->env_export);
		free_tok(tok);
		exit(g_sig_return);
	}
	if (args[i + 1])
	{
		if (!ft_exit_atoi(args[1]))
		{
			ft_printf("exit : %s: numeric argument required\n", args[1]);
			free_export(data->env_export);
			free_tab(args);
			free_tok(tok);
			exit(2);
		}
	}
	i = 0;
	if (args[i + 2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	exit_value = ft_atoi(args[1]);
	free_export(data->env_export);
	free_tab(args);
	free_tok(tok);
	exit(exit_value);
}
