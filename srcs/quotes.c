/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:15:53 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/10 01:27:17 by lbarry           ###   ########.fr       */
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

// char	find_next_quote(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 			return (str[i]);
// 		i++;
// 	}
// 	return ('\0');
// }

int	remove_quotes(char *str, char quote)
{
	int	i;
	int	in_quotes;

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
			// i-- if not we skip a char, since delchar deleted a char
			//new char at old adress
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
// exit syntax error if quotes are not closed
// then remove quotes if " found within ""
// same for ' within ''
// don't delete " within '' and vice versa

// int	remove_d_quotes(char *str)
// {
// 	int	i;
// 	int	in_quotes;

// 	i = 0;
// 	in_quotes = 0;
// 	while (str[i] && str[i] != '\'')
// 	{
// 		if (str[i] == '\"' && !in_quotes)
// 		{
// 			in_quotes = 1;
// 			del_char(&str[i], '\"');
// 			i--;
// 		}
// 		else if (str[i] == '\"' && in_quotes)
// 		{
// 			in_quotes = 0;
// 			del_char(&str[i], '\"');
// 			i--;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	remove_s_quotes(char *str)
// {
// 	int	i;
// 	int	in_quotes;

// 	i = 0;
// 	in_quotes = 0;
// 	while (str[i] && str[i] != '\"')
// 	{
// 		if (str[i] == '\'' && !in_quotes)
// 		{
// 			in_quotes = 1;
// 			del_char(&str[i], '\'');
// 			i--;
// 		}
// 		else if (str[i] == '\'' && in_quotes)
// 		{
// 			in_quotes = 0;
// 			del_char(&str[i], '\'');
// 			i--;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	manage_solo_quotes(char *input)
{
	printf("str before: %s\n", input);
	// only single quotes
	if (!ft_strchr(input, '\"'))
		remove_quotes(input, '\'');
	// only double quotes
	else if (!ft_strchr(input, '\''))
		remove_quotes(input, '\"');;
	printf("str after: %s\n", input);
	return (1);
}

// int manage_both_quotes(char *input)
// {
// 	// remove quotes found together but not within other quotes
// 	// e.g. "" '' ""BONJOUR

// 	return (0);
// }

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
	if (!ft_strchr(input, '\"') || !ft_strchr(input, '\''))
		manage_solo_quotes(input);
	// else
	//  	manage_both_quotes(input);
	return (0);
}
