/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:43:40 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 19:30:27 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen_from(int i, char *str)
{
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_access(char *cmd)
{
	if (ft_access(cmd) == 1)
		return (ft_strdup(cmd));
	else
		return (NULL);
}

char	ft_get_last_char(const char *str)
{
	while (*(str) && *(str + 1))
		++str;
	return (*str);
}
