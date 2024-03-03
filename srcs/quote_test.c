/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 04:34:56 by lbarry            #+#    #+#             */
/*   Updated: 2024/03/02 06:58:31 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

int	find_start_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	find_end_quotes(char *str, char c)
{
	int	strlen;

	strlen = ft_strlen(str) - 1;
	while (strlen)
	{
		if (str[strlen] == c)
			return (strlen);
		strlen--;
	}
	return (-1);
}
int	count_quotes_inside(char *str, char c, int start, int end)
{
	int	i;
	int	count;

	i = start + 1;
	count = 0;
	printf("start: %d\n", start);
	printf("end: %d\n", end);
	while (i < end)
	{
		if (str[i] == c)
			count++;
		printf("%c\n", str[i]);
		i++;
	}
	printf("count: %d\n", count);
	return (count);
}

size_t	ft_strlcpy(char *dest, const char *src, char c, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			if (src[i] == c)
				i++;
			else
			{
				dest[j] = src[i];
				i++;
				j++;
			}
		}
		dest[j] = '\0';
	}

	return (ft_strlen(src));
}
char	*ft_strdup(const char *s, char c)
{
	int		i;
	char	*copy;

	i = ft_strlen(s);
	copy = (char *)malloc(i + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, c, (i + 1));
	return (copy);
}

void	delete_quotes(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	printf("string before: %s\n", str);
	new_str = ft_strdup(str, c);
	printf("string after: %s\n", new_str);
}

int	manage_double_quotes(char *input)
{
	int		start_d_quotes;
	int		end_d_quotes;
	int		quote_count;
	char	*new_str = NULL;

	start_d_quotes = find_start_quotes(input, '\"');
	printf("start_d_quotes: %d\n", start_d_quotes);
	end_d_quotes = find_end_quotes(input, '\"');
	printf("end_d_quotes: %d\n", end_d_quotes);

	quote_count = count_quotes_inside(input, '\"', start_d_quotes, end_d_quotes);
	if (quote_count % 2 != 0)
	{
		printf("Error: quotes open\n");
		new_str = NULL;
		return (1);
	}
	else if (quote_count > 0 && quote_count % 2 == 0)
		delete_quotes(input, '\"');
	return (0);
}

int	manage_quotes(char *input)
{
	manage_double_quotes(input);
	// manage_single_quotes(input);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*input = NULL;

	if (argc == 2)
		input = argv[1];
	manage_quotes(input);
	return (0);
}
