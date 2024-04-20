/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:39:11 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/11 15:02:30 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

char	*find_envp_path(t_export *env)
{
	char		*path;
	t_export	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			path = ft_strdup(tmp->value);
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**split_path(t_data *data)
{
	char	*path;
	char	**split_path;

	path = find_envp_path(data->env_export);
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
	char	**tmp;
	char	*tmp2;
	char	*path;

	i = 0;
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
	return (free_tab(tmp), NULL);
}

void	init_data(int argc, t_data *data, t_token *tok)
{
	data->flag_hd = 0;
	data->argc = argc;
	data->nb_cmd = ft_count_pipe(tok);
	find_nb_hdoc(tok, data);
}
