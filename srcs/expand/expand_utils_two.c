/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:18:19 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/31 06:14:40 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_isalnum_env(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
	{
		return (1);
	}
	return (0);
}

int ft_tablen(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

int ft_find_malloc_key(char *str, int i)
{
    while(str[i] && ft_isalnum_env(str[i]))
        i++;
    return (i);
}

// Trying to find the key so later i can find the value with it
// key is the string before the = in the env list
// ex : USER=kboulkri, key is USER and value is kboulkri

char *ft_find_key(char *str, int count)
{
    int i;
    int j;
    int y;
    char *key;

    i = 0;
    y = 1;
    key = NULL;
    while(str[i])
    {
        if (str[i] == '$' && y == count)
        {
            j = 0;
            i++;
            key = malloc(ft_find_malloc_key(str, i) + 1);
            while(str[i] && ft_isalnum_env(str[i]))
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

int ft_strlen_from_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s_len;
	char	*str;

	if (!s1)
		return (NULL);
	s_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * ((s_len + 1)));
	if (!str)
	{
		return (NULL);
	}
	ft_strlcpy(str, (char *)s1, (ft_strlen(s1) + 1));
	ft_strlcat(str, (char *)s2, s_len + 1);
	return (str);
}
// Function to copy the envp and not to use the original one so we can modify it with export and set and unset



