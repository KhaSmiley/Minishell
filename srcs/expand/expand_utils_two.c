/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:18:19 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 20:12:56 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalnum_env(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z') || c == '_')
	{
		return (1);
	}
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_find_malloc_key(char *str, int i)
{
	while (str[i] && ft_isalnum_env(str[i]))
		i++;
	return (i);
}

// Trying to find the key so later i can find the value with it
// key is the string before the = in the env list
// ex : USER=kboulkri, key is USER and value is kboulkri

char	*ft_find_key(char *str, int count)
{
	int		i;
	int		j;
	int		y;
	char	*key;

	i = 0;
	y = 1;
	key = NULL;
	while (str[i])
	{
		if (str[i] == '$' && y == count)
		{
			j = 0;
			i++;
			key = ft_calloc(sizeof(char), ft_find_malloc_key(str, i) + 1);
			while (str[i] && ft_isalnum_env(str[i]))
				key[j++] = str[i++];
			key[j] = '\0';
			break ;
		}
		else if (str[i] == '$' && y != count)
			y++;
		i++;
	}
	return (key);
}

char	*ft_find_value(char *key, t_export *env)
{
	char		*stock;
	t_export	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			stock = tmp->value;
			if (!stock)
				return (NULL);
			return (stock);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
