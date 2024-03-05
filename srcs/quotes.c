/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:15:53 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/05 01:29:04 by lbarry           ###   ########.fr       */
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
	// if (!*address)
	// 	*address = "\n";
}

int	remove_quotes(char *str, char quote, t_input *flags)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	flags->dollar_flag = 0;
	// scan whole string for quotes
	while (str[i])
	{
		if (in_quotes && str[i] == '$' && quote == '\"')
		{
			flags->dollar_flag++;
			printf("dollar_flag: %d\n", flags->dollar_flag);
		}
		if (str[i] == quote && !in_quotes)
		{
			in_quotes = 1;
			// if quotes are found remove them
			del_char(&str[i], quote);
			// i-- if not we skip a char, since delchar deleted a char, new char at old adress
			i--;
		}
		else if (str[i] == quote && in_quotes)
		{
			in_quotes = 0;
			del_char(&str[i], quote);
			i--;
		}
		i++;
	}
	return (0);
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
// exit syntax error if quotes are not closed
// then remove quotes if " found within ""
// same for ' within ''
// don't delete " within '' and vice versa

int	in_d_quotes(char *str, t_input *flags)
{
	int	d_quotes;

	d_quotes = count_quotes(str, '\"');
	printf("d_quotes: %d\n", d_quotes);
	if (d_quotes % 2 != 0)
	{
		printf("Error: quotes open, syntax error\n");
		// free and exit syntax error
		return (-1);
	}
	else
	{
		printf("string before: %s\n", str);
		remove_quotes(str, '\"', flags);
		printf("string after: %s\n", str);
	}
	return (1);
}

int	in_s_quotes(char *str, t_input *flags)
{
	int	s_quotes;

	s_quotes = count_quotes(str, '\'');
	printf("s_quotes: %d\n", s_quotes);
	if (s_quotes % 2 != 0)
	{
		printf("Error: quotes open, syntax error\n");
		// free and exit sytax error
		return (-1);
	}
	else
	{
		printf("string before: %s\n", str);
		remove_quotes(str, '\'', flags);
		printf("string after: %s\n", str);
	}
	return (1);
}

int	manage_quotes(char *str, t_input *flags)
{
	if (!ft_strchr(str, '\"') && !ft_strchr(str, '\''))
		return (printf("no quotes\n"), 0);
	else if (!ft_strchr(str, '\"'))
		in_s_quotes(str, flags);
	else if (!ft_strchr(str, '\''))
		in_d_quotes(str, flags);
	else if (ft_strchr(str, '\"') < ft_strchr(str, '\''))
		in_d_quotes(str, flags);
	else
		in_s_quotes(str, flags);
	return (1);
}
