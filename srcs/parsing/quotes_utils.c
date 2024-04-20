/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 03:59:41 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 19:40:36 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// count quotes- apart from ones inside of same type
// open quotes error
// if only one type of quotes- remove them
// if both types of quotes- only remove outside ones

int	check_closure(char *str, int i, char quote, int flag)
{
	if (!str)
		return (-2);
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == quote && flag == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	s_quotes_open(char *str)
{
	int	i;
	int	d_flag;

	d_flag = 0;
	i = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] != '\'')
		{
			if (!d_flag && str[i] == '\"')
				d_flag = 1;
			else if (d_flag && str[i] == '\"')
				d_flag = 0;
		}
		if (str[i] && str[i] == '\'' && d_flag == 0)
		{
			if (check_closure(str, i, '\'', d_flag) == -1)
				return (0);
			i = check_closure(str, i, '\'', d_flag);
		}
		i++;
	}
	return (1);
}

int	d_quotes_open(char *str)
{
	int	i;
	int	s_flag;

	i = 0;
	s_flag = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] != '\"')
		{
			if (!s_flag && str[i] == '\'')
				s_flag = 1;
			else if (s_flag && str[i] == '\'')
				s_flag = 0;
		}
		if (str[i] && str[i] == '\"' && s_flag == 0)
		{
			if (check_closure(str, i, '\"', s_flag) == -1)
				return (0);
			i = check_closure(str, i, '\"', s_flag);
		}
		i++;
	}
	return (1);
}

int	count_quotes(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	check_quotes_open(char *input)
{
	int	s_quotes;
	int	d_quotes;

	if (!input)
		return (1);
	if (!ft_strchr(input, '\"') || !ft_strchr(input, '\''))
	{
		s_quotes = count_quotes(input, '\'');
		d_quotes = count_quotes(input, '\"');
		if (s_quotes % 2 != 0 || d_quotes % 2 != 0)
			return (0);
	}
	else
	{
		if (!s_quotes_open(input))
			return (0);
		if (!d_quotes_open(input))
			return (0);
	}
	return (1);
}
