/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:39:43 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/09 17:22:52 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	choose_return(t_data *data)
{
	int	ret;

	if (g_sig_return)
	{
		ret = g_sig_return;
		g_sig_return = 0;
		return (ret);
	}
	return (data->status);
}

char	*normal(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '$' && str[*i] != '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*single_quote(char *str, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_strjoinou(char *s1, char *s2)
{
	int		i;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	res = malloc(ft_strl(s1) + ft_strl(s2) + 1);
	if (!res)
		return (NULL);
	while (i < ft_strl(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (i < ft_strl(s1) + ft_strl(s2))
	{
		res[i] = s2[i - ft_strl(s1)];
		i++;
	}
	res[i] = 0;
	free(s1);
	free(s2);
	return (res);
}
