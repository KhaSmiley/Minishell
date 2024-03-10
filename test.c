#include <stdio.h>
#include <string.h>

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
int main()
{
	// ''""""
	char *str = "\"\'\'\'\"\"";
	printf("%d\n", lonely_d_quote_count(str));

    return (0);
}
