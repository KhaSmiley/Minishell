/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:38 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 06:48:17 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing_and_stock_input(char *input, t_token **tok, t_data *data)
{
	t_token	*tmp;

	tmp = *tok;
	if (!manage_quote_errors(input))
	{
		free(input);
		free_tok(tok);
		data->status = 2;
		return (1);
	}
	tmp = find_token(input);
	if (ft_syntax(&tmp))
	{
		free(input);
		free_tok(&tmp);
		return (1);
	}
	ft_expand_str_y(tmp, data);
	fix_quotes_token(tmp);
	*tok = tmp;
	return (0);
}

int	ft_syntax_pipe(t_token *tok)
{
	t_token	*tmp;

	if (!tok)
		return (1);
	tmp = tok;
	if (tmp->type == PIPE)
		return (1);
	else if (tmp->type == WORD)
	{
		tmp = tmp->next;
		if (ft_syntax_word(tmp->next))
			return (1);
	}
	else if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
		|| tmp->type == DLESS)
	{
		tmp = tmp->next;
		if (ft_syntax_redir(tmp))
			return (1);
	}
	else if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
		|| tmp->type == DLESS)
	{
		tmp = tmp->next;
		if (ft_syntax_redir(tmp))
			return (1);
	}
	return (0);
}

int	ft_syntax_redir(t_token *tok)
{
	t_token	*tmp;

	if (!tok)
		return (1);
	tmp = tok;
	if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
		|| tmp->type == DLESS)
		return (1);
	else if (tmp->type == PIPE)
		return (1);
	else if (tmp->type == WORD)
	{
		tmp = tmp->next;
		if (ft_syntax_word(tmp->next))
			return (1);
	}
	return (0);
}

int	ft_syntax_word(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp && tmp->type == WORD)
		tmp = tmp->next;
	if (!tmp)
		return (0);
	if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
		|| tmp->type == DLESS)
	{
		if (ft_syntax_redir(tmp->next))
		{
			if (tmp->next)
				ft_printf("syntax error near unexpected token '%s'\n",
					tmp->next->str);
			else
				ft_printf("syntax error near unexpected token 'newline'\n");
			return (1);
		}
		tmp = tmp->next;
	}
	else if (tmp->type == PIPE)
	{
		if (ft_syntax_pipe(tmp->next))
		{
			if (tmp->next)
				ft_printf("syntax error near unexpected token '%s'\n",
					tmp->next->str);
			else
				ft_printf("syntax error near unexpected token 'newline'\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_syntax(t_token **tok)
{
	t_token	*tmp;

	tmp = *tok;
	if (!tmp)
		return (0);
	if ((tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
			|| tmp->type == DLESS))
	{
		if (tmp->next == NULL)
			return (ft_printf("syntax error near unexpected token `newxline'\n"),
				-1);
		tmp = tmp->next;
		if (ft_syntax_redir(tmp))
			return (ft_printf("syntax error near unexpected token '>'\n"), -1);
	}
	else if (tmp->type == PIPE)
		return (ft_printf("syntax error near unexpected token '|'\n"), -1);
	else if (tmp->type == WORD)
	{
		tmp = tmp->next;
		if (ft_syntax_word(tmp))
			return (ft_printf("check which error message\n"), -1);
	}
	return (0);
}
