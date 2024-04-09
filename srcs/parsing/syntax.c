/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:38 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/09 07:58:05 by kboulkri         ###   ########.fr       */
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
	ft_expand_str(tmp, data);
	fix_quotes_token(tmp);
	data->tok = tmp;
	return (0);
}

int	ft_syntax_pipe(t_token *tok, int *error)
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
		if (ft_syntax_word(tmp, error))
			return (1);
	}
	else if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
		|| tmp->type == DLESS)
	{
		tmp = tmp->next;
		if (ft_syntax_redir(tmp, error))
			return (1);
	}
	return (0);
}
void	choose_error_value(t_token *tmp, int *error)
{
	if (tmp->type == GREATER)
		(*error) = 3;
	else if (tmp->type == LESS)
		(*error) = 4;
	else if (tmp->type == DGREATER)
		(*error) = 5;
	else if (tmp->type == DLESS)
		(*error) = 6;
}

int	ft_syntax_redir(t_token *tok, int *error)
{
	t_token	*tmp;

	if (!tok)
		return (1);
	tmp = tok;
	if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
		|| tmp->type == DLESS)
	{
		choose_error_value(tmp, error);
		return (1);
	}
	else if (tmp->type == PIPE)
	{
		(*error) = 2;
		return (1);
	}
	else if (tmp->type == WORD)
	{
		tmp = tmp->next;
		if (ft_syntax_word(tmp, error))
			return (1);
	}
	return (0);
}

int	ft_syntax_word(t_token *tok, int *error)
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
		tmp = tmp->next;
		if (ft_syntax_redir(tmp, error))
			return (1);
	}
	else if (tmp->type == PIPE)
	{
		tmp = tmp->next;
		if (ft_syntax_pipe(tmp, error))
		{
			(*error) = 2;
			return (1);
		}
	}
	return (0);
}

int	ft_syntax(t_token **tok)
{
	t_token	*tmp;
	int	error = 0;

	tmp = *tok;
	if (!tmp)
		return (0);
	if ((tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER
			|| tmp->type == DLESS))
	{
		if (tmp->next == NULL)
			return (ft_printf("syntax error near unexpected token `newline'\n"), 1);
		tmp = tmp->next;
		if (ft_syntax_redir(tmp, &error))
		{
			if (error == 2)
				return (ft_printf("syntax error near unexpected token '|'\n"), 1);
			else if (error == 3)
				return (ft_printf("syntax error near unexpected token '>'\n"), 1);
			else if (error == 4)
				return (ft_printf("syntax error near unexpected token '<'\n"), 1);
			else if (error == 5)
				return (ft_printf("syntax error near unexpected token '>>'\n"), 1);
			else if (error == 6)
				return (ft_printf("syntax error near unexpected token '<<'\n"), 1);
			else
				return (ft_printf("syntax error near unexpected token `newline'\n"), 1);
		}
	}
	else if (tmp->type == PIPE)
		return (ft_printf("syntax error near unexpected token '|'\n"), 1);
	else if (tmp->type == WORD)
	{
		tmp = tmp->next;
		if (ft_syntax_word(tmp, &error))
		{
			if (error == 2)
				return (ft_printf("syntax error near unexpected token '|'\n"), 1);
			else
				return (ft_printf("syntax error near unexpected token `newline'\n"), 1);
		}
	}
	return (0);
}
