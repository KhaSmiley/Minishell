/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:38 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/26 22:50:16 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_syntax_pipe(t_token *tok)
{
    t_token *tmp;
    
    if (!tok)
        return (-1);
    tmp = tok;
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
        return (-1);
    else if (tmp->type == PIPE)
        return (-1);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        if (ft_syntax_word(tmp))
            return (-1);
    }
    else
        return (0);
}

int ft_syntax_redir(t_token *tok)
{
    t_token *tmp;

    if(!tok)
        return (-1);
    tmp = tok;
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
        return (-1);
    else if (tmp->type == PIPE)
        return (-1);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        if (ft_syntax_word(tmp))
            return (-1);
    }
    else
        return (0);
}

int ft_syntax_word(t_token *tok)
{
    t_token *tmp;

    if (!tok)
        return (0);
    tmp = tok;
    while (tmp->type == WORD)
        tmp = tmp->next;
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
    {
        tmp = tmp->next;
        if(ft_syntax_redir(tmp))
            return (-1);
    }
    else if (tmp->type == PIPE)
    {
        tmp = tmp->next;
        if (ft_syntax_pipe(tmp))
            return (-1);
    }
    else
        return (0);
}

int ft_syntax(t_token *tok)
{
    t_token *tmp;

    tmp = tok;
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
    {
        tmp = tmp->next;
        if (ft_syntax_redir(tmp))
            return (printf("syntax error"), -1);
        else
            return (0);            
    }
    else if (tmp->type == PIPE)
        return (printf("syntax error near unexpected token '|'\n"), -1);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        if (ft_syntax_word(tmp));
            return (printf("Syntax Error\n"), -1);
    }
}