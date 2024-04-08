/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 04:48:21 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 04:11:10 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	word_size(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '>' && str[i] != '<'
		&& str[i] != '|' && str[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);
}

int	ft_find_end(char *str, char flag_quotes, int i)
{
	while (str[i])
	{
		i++;
		if ((str[i] == '\0') || ((str[i] == flag_quotes) && (str[i + 1] == ' '
					|| str[i + 1] == '\t')))
			return (i);
	}
	return (i);
}

char	*topositif(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < 0)
			str[i] = -str[i];
	return (str);
}

char	*tonegatif(char *str)
{
	char	flag_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag_quote = str[i++];
			while (str[i] != flag_quote)
			{
				str[i] = -str[i];
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (str);
}
