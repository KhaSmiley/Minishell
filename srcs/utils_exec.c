/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:39:11 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/21 15:18:03 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

char	*find_envp_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen_from(5, envp[i]));
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**split_path(t_data *data)
{
	int		i;
	int		j;
	char	*path;
	char	**split_path;

	i = 0;
	j = 0;
	path = find_envp_path(data->envp_cpy);
	if (!path)
		return (NULL);
	data->count_tab = ft_count_word(path, ':');
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	free(path);
	return (split_path);
}

char	*complete_path(t_data *data, char *cmd)
{
	int		i;
	int		j;
	char	**tmp;
	char	*tmp2;
	char	*path;

	i = 0;
	j = 0;
	tmp2 = NULL;
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup_access(cmd));
	tmp = split_path(data);
	if (!tmp)
		return (NULL);
	while (tmp[i])
	{
		tmp2 = ft_strjoin(tmp[i], "/");
		path = ft_strjoin(tmp2, cmd);
		if (ft_access(path) == 1)
			return (free(tmp2), free_tab(tmp), path);
		free(tmp2);
		free(path);
		i++;
	}
	return (free_tab(tmp), ft_printf("%s: complete path command not found\n", cmd), NULL);
}

void	init_data(int argc, t_data *data, t_token *tok)
{
	data->argc = argc;
	data->nb_cmd = ft_count_pipe(tok);
}