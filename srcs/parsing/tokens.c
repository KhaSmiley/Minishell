/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:06:11 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/04 03:58:44 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_tokenizer(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (LESS);
	else if (ft_strcmp(token, ">") == 0)
		return (GREATER);
	else if (ft_strcmp(token, "<<") == 0)
		return (DLESS);
	else if (ft_strcmp(token, ">>") == 0)
		return (DGREATER);
	else if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token, " ") == 0)
		return (WHITE_SPACE);
	else
		return (WORD);
}

int	word_size(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '>' && str[i] != '<'
		&& str[i] != '|' && str[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);
}

int	alloc_token(t_token **tok, char *longchev, char *str, int i)
{
	int		j;
	char	*redirection;

	j = 0;
	if (str[i + 1] == longchev[0])
	{
		redirection = ft_strdup(longchev);
        if (!redirection)
            return (-1);
		ft_stock(tok, ft_lstnew(redirection, ft_tokenizer(redirection)));
		return (1);
	}
    redirection = ft_strdup(&longchev[1]);
	if (!redirection)
		return (-1);
	ft_stock(tok, ft_lstnew(redirection, ft_tokenizer(redirection)));
	return (0);
}

int	ft_find_end(char *str, char flag_quotes, int i)
{
	while (str[i])
	{
		i++;
		if ((str[i] == '\0') || ((str[i] == flag_quotes) && (str[i + 1] == ' ' || str[i + 1] == '\t')))
			return (i);
	}
	return (i);
}

char	*topositif(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < 0)
			str[i] = -str[i];
	return (str);
}

char	*tonegatif(char *str)
{
	char	flag_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag_quote = str[i++];
			while (str[i] != flag_quote)
			{
				str[i] = -str[i];
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (str);
}

char	*isaword(char *str, int *i)
{
    int j = 0;
    char *word;
	word = ft_calloc(word_size(str, *i) + 1, 1);
	if (!word)
		return (NULL);
	while (ft_strchr(" \t><|\0", str[*i]) == 0)
		word[j++] = str[(*i)++];
    return (word);
}

t_token	*find_token(char *str)
{
	int		i;
	t_token	*tok;

	tok = NULL;
	i = 0;
	tonegatif(str);
	while (str[i])
	{
		if (str[i] == '<')
			i += alloc_token(&tok, "<<", str, i);
		else if (str[i] == '>')
			i += alloc_token(&tok, ">>", str, i);
		else if (str[i] == '|')
			ft_stock(&tok, ft_lstnew(ft_strdup("|"), PIPE));
		else if (str[i] == ' ' || str[i] == '\t')
			ft_tokenizer(" ");
		else
			ft_stock(&tok, ft_lstnew(topositif(isaword(str, &i)), WORD));
		if (str[i])
			i++;
	}
	return (tok);
}
