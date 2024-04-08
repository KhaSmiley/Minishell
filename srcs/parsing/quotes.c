/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:15:53 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/08 20:07:18 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	set_in_quotes_flag(int *flag)
{
	if (!(*flag))
		(*flag) = 1;
	else
		(*flag) = 0;
}

int	remove_quotes(char *str)
{
	int	i;
	int	in_d_quotes;
	int	in_s_quotes;

	i = -1;
	in_d_quotes = 0;
	in_s_quotes = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '\"' && !in_s_quotes)
		{
			set_in_quotes_flag(&in_d_quotes);
			del_char(&str[i], '\"');
			i--;
		}
		else if (str[i] == '\'' && !in_d_quotes)
		{
			set_in_quotes_flag(&in_s_quotes);
			del_char(&str[i], '\'');
			i--;
		}
	}
	return (1);
}

int	manage_quote_errors(char *input)
{
	if (!ft_strchr(input, '\"') && !ft_strchr(input, '\''))
		return (1);
	if (!check_quotes_open(input))
	{
		printf("Syntax error: quotes open\n");
		return (0);
	}
	return (1);
}

t_token	*fix_quotes_token(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			remove_quotes(tmp->str);
			if (tmp->str[0] == '\0')
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
	return (tok);
}
