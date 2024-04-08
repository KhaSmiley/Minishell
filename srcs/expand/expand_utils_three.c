/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:37:45 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 04:13:12 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen_from_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_strl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	ft_find_value_malloc(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[start] && (ft_isalnum(str[start]) || str[start] != '_'))
		start++;
	return (start);
}

char	*to_next_double_q(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

int	is_last(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count % 2);
}
