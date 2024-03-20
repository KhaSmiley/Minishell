/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:43:40 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/19 02:13:22 by kboulkri         ###   ########.fr       */
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
		return (cmd);
	else
		return (ft_printf("%s: command not found\n", cmd), NULL);
}

