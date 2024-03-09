#include "../include/minishell.h"

// count quotes- apart from ones inside of same type
// open quotes error
// if only one type of quotes- remove them
// if both types of quotes- only remove outside ones

int	find_another_quote(char *input, char quote, int i)
{
	while (input[i])
	{
		if (input[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

int	lonely_s_quote_count(char *input)
{
	int	i;
	int	count;
	int	in_d_quotes;

	i = 0;
	count = 0;
	in_d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			in_d_quotes = 1;
		else if (in_d_quotes)
		{
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] == '\"')
				in_d_quotes = 0;
		}
		else if (!in_d_quotes && input[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	lonely_d_quote_count(char *input)
{
	int	i;
	int	count;
	int	in_s_quotes;

	i = 0;
	count = 0;
	in_s_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			in_s_quotes = 1;
		else if (in_s_quotes)
		{
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\'')
				in_s_quotes = 0;
		}
		else if (!in_s_quotes && input[i] && input[i] == '\"')
			count++;
		i++;
	}
	return (count);
}
int manage_both_quotes(char *input)
{
	int	d_count = 0;
	int	s_count = 0;
	s_count = lonely_s_quote_count(input);
	d_count = lonely_d_quote_count(input);
	printf("d_count: %d\n", d_count);
	printf("s_count: %d\n", s_count);
	if (d_count % 2 != 0 || s_count % 2 != 0)
	{
		printf("Syntax error: quotes open\n");
		return (-1);
	}
	return (0);
}
int	manage_quotes(char *input)
{
	if (!ft_strchr(input, '\"') && !ft_strchr(input, '\''))
		return (printf("no quotes\n"), 0);
	if (!ft_strchr(input, '\"') || !ft_strchr(input, '\''))
		manage_solo_quotes(input);
	// first count quotes (outside of word) check if open
	else
		manage_both_quotes(input);

	// remove quotes found together but not within other quots
	// e.g. "" '' ""BONJOUR

	return (0);
}


