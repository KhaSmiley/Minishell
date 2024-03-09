/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:22:20 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/09 05:05:53 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
//scan through each chars
//if a quote is encountered
//enter listening state => waiting for closure
//if not closed => trow syntax error

//"weifgu'as'cds"""""""""'

int check_closure(char *str, int i, char quote)
{
	int in_quotes = 1;
	i++;
	while (str[i] && in_quotes)
	{
		if (str[i] == quote)
			in_quotes = 0;
		i++;
	}
	if (in_quotes)
	{
		write(1, "KO", 2);
		return (0);
	}
	return (i);
}

int main(void)
{
	int i = 0;
	char *str = "we\'if\"g\'uascds\"\"\"";
	while (str[i])
	{
		while (str[i] && str[i] != '\"' && str[i] != '\'')
			i++;
		if (str[i] == '\"')
			i += check_closure(str, i, '\"');
		else if (str[i] == '\'')
			i += check_closure(str, i, '\'');
		i++;
	}
	return (0);
}

