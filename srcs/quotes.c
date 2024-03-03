/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:15:53 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/03 23:52:25 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;
	char			*str;

	i = 0;
	d = (unsigned char)c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == d)
			return (&str[i]);
		i++;
	}
	if (str[i] == d)
		return (&str[i]);
	return (0);
}

// del char " or ' from string and move rest of string forwards in memory
void	del_char(char *address, char char_to_del)
{
	while (*address != '\0' && *address != char_to_del)
		address++;
	if (*address == char_to_del)
	{
		while (*address != '\0')
		{
			// seg fault- adress protected - try mallocing string first
			*address = *(address + 1);
			address++;
		}
	}
}

int	remove_quotes(char *str, char quote)
{
	int	in_quotes;
	int	i;

	i = 0;
	in_quotes = 0;
	// scan whole string for quotes
	while (str[i])
	{
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

int	manage_quotes(char *str)
{
	int	quote_count;

	quote_count = count_quotes(str, '\"');
	if (quote_count % 2 != 0)
	{
		printf("Error: quotes open\n");
		return (quote_count);
	}
	else
	{
		remove_quotes(str, '\"');
		//printf("string after: %s\n", str);
	}
	return (quote_count);
}

int	main(void)
{
	char	*input;

	input = "\"\"hello world\"\"";
	printf("%s\n", input);
	// printf("%d\n", manage_quotes(input));
	del_char(input, '\"');
	printf("%s\n", input);

	return (0);
}
