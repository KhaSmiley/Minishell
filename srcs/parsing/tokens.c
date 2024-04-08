/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:06:11 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/08 04:05:05 by kboulkri         ###   ########.fr       */
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

int	alloc_token(t_token **tok, char *longchev, char *str, int i)
{
	char	*redirection;

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

char	*isaword(char *str, int *i)
{
	int		j;
	char	*word;

	j = 0;
	word = ft_calloc(word_size(str, *i) + 1, 1);
	if (!word)
		return (NULL);
	while (ft_strchr(" \t><|\0", str[*i]) == 0)
	{
		word[j++] = str[(*i)++];
	}
	if (str[*i])
		(*i)--;
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
		{
			ft_stock(&tok, ft_lstnew(ft_strdup("|"), PIPE));
		}
		else if (str[i] == ' ' || str[i] == '\t')
			ft_tokenizer(" ");
		else
			ft_stock(&tok, ft_lstnew(topositif(isaword(str, &i)), WORD));
		if (str[i])
			i++;
	}
	return (tok);
}
