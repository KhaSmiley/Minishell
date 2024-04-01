/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:06:11 by lbarry            #+#    #+#             */
/*   Updated: 2024/04/01 19:43:04 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int     ft_tokenizer(char *token)
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

int word_size(char *str, int i)
{
    int j;

    j = 0;
    while(str[i] != ' ' && str[i] != '\t' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\0')
    {
        j++;
        i++;
    }
    return (j);
}


int    alloc_token(t_token **tok, char *longchev, char *str, int i)
{
	int		j;
	char	*redirection;

	j = 0;
	if (str[i + 1] == longchev[0])
	{
		redirection = malloc(sizeof(char) * 3);
		if (!redirection)
			return (-1);
		while (j < 2)
		{
			redirection[j] = longchev[j];
			j++;
		}
		redirection[j] = '\0';
		ft_stock(tok, ft_lstnew(redirection, ft_tokenizer(redirection)));
		return (1);
	}
	redirection = malloc(sizeof(char) * 2);
	if (!redirection)
		return (-1);
	redirection[0] = longchev[0];
	redirection[1] = '\0';
	ft_stock(tok, ft_lstnew(redirection, ft_tokenizer(redirection)));
	return (0);
}

int ft_find_end(char *str, char flag_quotes, int i)
{
    int stop;
    stop = 0;
    while(str[i])
    {
        i++;
        if (str[i] == '\0' || ((str[i] == flag_quotes) && str[i + 1] == ' '))
        {
            stop = i;
            break ;
        }    
    }
    return(stop);
}

t_token    *find_token(char *str)
{
    int i;
    int j;
    char *word;
    t_token *tok;
    char flag_quote;
    int stop;

    tok = NULL;
    i = 0;
    flag_quote = '\0';
    while(str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
		    check_quotes_for_env(&flag_quote, str, i);
        if (flag_quote == '\0')
        {
            if (str[i] == '<')
                i += alloc_token(&tok, "<<", str, i);
            else if (str[i] == '>')
                i += alloc_token(&tok, ">>", str, i);
            else if (str[i] == '|')
            {
                word = malloc(sizeof(char) * 2);
                if (!word)
                    return (NULL);
                word[0] = '|';
                word[1] = '\0';
                ft_stock(&tok, ft_lstnew(word, ft_tokenizer(word)));
            }
            else if (str[i] == ' ' || str[i] == '\t')
                ft_tokenizer(" ");
            else
            {
                j = 0;
                word = malloc(word_size(str, i) + 1);
                if (!word)
                    return (NULL);
                while (ft_strchr(" \t><|\0", str[i]) == 0)
                    word[j++] = str[i++];
                word[j] = '\0';
                ft_stock(&tok, ft_lstnew(word, ft_tokenizer(word)));
                i--;
            } 
        }
        else
        {
            if (flag_quote == '\'' || flag_quote == '\"')
            {
                j = 0;
                word = malloc(ft_find_end(str, flag_quote, i) + 1);
                if (!word)
                    return (NULL);
                stop = ft_find_end(str, flag_quote, i);
                while (i <= stop)
                    word[j++] = str[i++];
                word[j] = '\0';
                ft_stock(&tok, ft_lstnew(word, ft_tokenizer(word)));
                i--;
                flag_quote = '\0';
            }
        }
        i++;
    }
    print_list(tok);
	return (tok);
}
