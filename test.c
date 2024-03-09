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
int main()
{
	// ''""""
	char *str = "\"\'\'\'\"\"";
	printf("%d\n", lonely_d_quote_count(str));

    return (0);
}
