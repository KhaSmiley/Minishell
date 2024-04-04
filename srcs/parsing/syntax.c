/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:38 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/04 03:58:42 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing_and_stock_input(char *input, t_token **tok, t_data *data)
{
	t_token	*tmp;

	tmp = *tok;
	if (!manage_quote_errors(input))
		return (1);
	tmp = find_token(input);
    if (ft_syntax(&tmp))
		return (1);
        
	ft_expand_str_y(tmp, data);
	fix_quotes_token(tmp);
	*tok = tmp;
	return (0);
}

int ft_syntax_pipe(t_token *tok)
{
    t_token *tmp;

    if (!tok)
        return (12);
    tmp = tok;
    if (tmp->type == PIPE)
        return (35);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        if (ft_syntax_word(tmp))
            return (59);
    }
    return (0);
}

int ft_syntax_redir(t_token *tok)
{
    t_token *tmp;

    if(!tok)
        return (112);
    tmp = tok;
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
        return (1543);
    else if (tmp->type == PIPE)
        return (13252);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        if (ft_syntax_word(tmp))
            return (154354);
    }
    return (0);
}

int ft_syntax_word(t_token *tok)
{
    t_token *tmp;
    int error;

    tmp = tok;
    while (tmp && tmp->type == WORD)
        tmp = tmp->next;
    if (!tmp)
        return (0);
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
    {
        tmp = tmp->next;
        error = ft_syntax_redir(tmp);
        if (error)
            return (error);
    }
    else if (tmp->type == PIPE)
    {
        tmp = tmp->next;
        error = ft_syntax_pipe(tmp);
        if (error)
            return (error);
    }
    return (0);
}

int ft_syntax(t_token **tok)
{
    t_token *tmp;

    int error;
    tmp = *tok;
	// double check how to handle empty input later
	if (!tmp)
		return (0);
	if ((tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS))
    {
        if (tmp->next == NULL)
            return (ft_printf("syntax error near unexpected token `newline'\n"), -1);
        tmp = tmp->next;
        error = ft_syntax_redir(tmp);
        if (error)
            return (ft_printf("Syntax Error [%i]\n", error), -1);
        return (0);
    }
    else if (tmp->type == PIPE)
        return (ft_printf("syntax error near unexpected token '|'\n"), -1);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        error = ft_syntax_word(tmp);
        if (error)
            return (ft_printf("Syntax Error [%i]\n", error), -1);
    }
    return (0);
}
