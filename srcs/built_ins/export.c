/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:13:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/30 04:32:42 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_find_key_export(char *str)
{
    int i;
    int j;
    char *key;

    key = NULL;
    i = 0;
	j = 0;
	key = malloc(ft_find_malloc_key(str, i) + 1);
	while(str[i] && (ft_isalnum_env(str[i])))
		key[j++] = str[i++];
	key[j] = '\0';
    return (key);
}

char *ft_find_value_export(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while(str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_strdup(&str[i + 1]));
}


void print_list_export(t_export *lst)
{
    if (!lst)
		return ;
    while(lst)
    {
        printf("%s=%s\n", lst->key, lst->value);
        lst = lst->next;
    }
    return ;
}

void	ft_delone_export(t_export **env, char *key)
{
	t_export *tmp;
	t_export *prev;

	prev = *env;
	if (env && !ft_strcmp((*env)->key, key))
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		free(key);
		return ;
	}
	tmp = (*env)->next;
	while (tmp && ft_strcmp(tmp->key, key))
	{
		prev = prev->next;
		tmp = tmp->next;
	}
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		prev->next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(key);
}

int ft_check_syntax_key(char *str)
{
	int i;

	i = 0;
	if (str[i] == '=')
		return (1);
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum_env(str[i]) && str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

void ft_export(t_data *data, char **args)
{
	int i;
	i = 1;

	ft_envp_copy_export(data);
	while(args[i])
	{
		if (ft_check_syntax_key(args[i]))
		{
			printf("export: `%s': not a valid identifier\n", args[i]);
			i++;
			continue;
		}
		if (ft_strchr(args[i], '='))
		{
			if (check_if_key_exist_export(data->env_export, args[i]))
			{
				ft_delone_export(&data->env_export, ft_find_key_export(args[i]));
			}
			ft_stock_export(&data->env_export, ft_lstnew_export(ft_find_key_export(args[i]), ft_find_value_export(args[i])));
		}
		else
			break ;
		i++;
	}
	return ;
}

void ft_envp_copy_export(t_data *data)
{
	int i;

	i = 0;
	while(data->envp_cpy[i])
	{
		ft_stock_export(&data->env_export, ft_lstnew_export(ft_find_key_export(data->envp_cpy[i]), ft_find_value_export(data->envp_cpy[i])));
		i++;
	}
}
