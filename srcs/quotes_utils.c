#include "../include/minishell.h"

// count quotes- apart from ones inside of same type
// open quotes error
// if only one type of quotes- remove them
// if both types of quotes- only remove outside ones

int check_closure(char *str, int i, char quote, int flag)
{
	char other;

	if (quote == '\'')
		other = '\"';
	else
		other = '\'';
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
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != '\'')
		{
			if (!d_flag && str[i] == '\"')
				d_flag = 1;
			else if (d_flag && str[i] == '\"')
				d_flag = 0;
			i++;
		}
		if (str[i] == '\'' && d_flag == 0)
		{
			if (check_closure(str, i, '\'', d_flag) == -1)
				return (printf("Error: s quotes open\n"), 0);
			else
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
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != '\"')
		{
			if (!s_flag && str[i] == '\'')
				s_flag = 1;
			else if (s_flag && str[i] == '\'')
				s_flag = 0;
			i++;
		}
		if (str[i] == '\"' && s_flag == 0)
		{
			if (check_closure(str, i, '\"', s_flag) == -1)
				return (printf("Error: d quotes open\n"), 0);
			else
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

int	check_solo_quotes_open(char *input)
{
	int s_quotes;
	int d_quotes;

	s_quotes = count_quotes(input, '\'');
	printf("s_quotes: %d\n", s_quotes);
	d_quotes = count_quotes(input, '\"');
	printf("d_quotes: %d\n", d_quotes);
	if (s_quotes % 2 != 0 || d_quotes % 2 != 0)
		return (0);
	return (1);
}

int	check_quotes_open(char *input)
{
	if (!ft_strchr(input, '\"') || !ft_strchr(input, '\''))
	{
		if (!check_solo_quotes_open(input))
			return (0);
	}
	else
	{
		if (!s_quotes_open(input) || !d_quotes_open(input))
			return (0);
	}
	return (1);
}




