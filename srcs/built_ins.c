/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:49:03 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/19 01:54:06 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	to_builtin_or_not_to_builtin(t_token *tok, char **envp_cpy)
{
	(void)envp_cpy;
	t_token	*tmp;

	tmp = tok;
	while (tmp && tmp->type != PIPE)
	{
		if (!ft_strncmp(tmp->str, "pwd", 3))
			ft_pwd();
		// else if (!ft_strncmp(tmp->str, "cd", 2))
		// 	ft_cd(tok, envp_cpy);
		tmp = tmp->next;
	}
	return (1);
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


// int	ft_cd(t_token *tok, char **envp_cpy)
// {
// 	char	*path;
// 	int		ret;
// 	t_token	*tmp;

// 	(void)envp_cpy;
// 	tmp = tok;
	// if no args go to HOME - find HOME in envp_cpy and send to chdir
	// create find_str_in_envp_cpy func
	// if (!tmp->next)
	// {
	// 	path = ft_strdup("HOME");
	// 	if (!path)
	// 		return (0);
	// }

	// check 1 arg (if not error)

	// do we need to malloc???

	// if (tmp->next)
	// {
	// 	path = tmp->next->str;
	// }
// 	ret = chdir(path);
// 	if (ret == -1)
// 	{
// 		printf("cd: %s: No such file or directory\n", path);
// 		return (0);
// 	}
// 	return (1);
// }
