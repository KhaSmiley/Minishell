/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:15:53 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/10 20:39:21 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// del char " or ' from string and move rest of string forwards in memory
// merci bilel
void	del_char(char *address, char char_to_del)
{
	while (*address != '\0' && *address != char_to_del)
		address++;
	if (*address == char_to_del)
	{
		while (*address != '\0')
		{
			*address = *(address + 1);
			address++;
		}
	}
}

int	remove_quotes(char *str)
{
	int	i;
	int	in_d_quotes;
	int	in_s_quotes;

	i = 0;
	in_d_quotes = 0;
	in_s_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !in_s_quotes)
		{
			if (!in_d_quotes)
				in_d_quotes = 1;
			else
				in_d_quotes = 0;
			del_char(&str[i], '\"');
			i--;
		}
		else if (str[i] == '\'' && !in_d_quotes)
		{
			if (!in_s_quotes)
				in_s_quotes = 1;
			else
				in_s_quotes = 0;
			del_char(&str[i], '\'');
			i--;
		}
		i++;
	}
	return (0);
}

int	manage_quotes(char *input)
{
	// check quotes open
	// $ stock expands
	// remove quotes

	// no quotes
	if (!ft_strchr(input, '\"') && !ft_strchr(input, '\''))
		return (printf("no quotes\n"), 0);
	// check quotes open
	if (!check_quotes_open(input))
	{
		printf("Syntax error: quotes open\n");
		exit(1);
	}
	// --> insert $ stuff here before removing quotes

	// remove quotes
	printf("input: %s\n", input);
	remove_quotes(input);
	printf("after remove quotes: %s\n", input);
	return (0);
}
