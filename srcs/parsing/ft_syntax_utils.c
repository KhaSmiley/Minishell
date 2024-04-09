/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 08:22:31 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/09 08:43:22 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_syntax_error_message(int error)
{
	if (error == 2)
		ft_printf("syntax error near unexpected token '|'\n");
	else if (error == 3)
		ft_printf("syntax error near unexpected token '>'\n");
	else if (error == 4)
		ft_printf("syntax error near unexpected token '<'\n");
	else if (error == 5)
		ft_printf("syntax error near unexpected token '>>'\n");
	else if (error == 6)
		ft_printf("syntax error near unexpected token '<<'\n");
	else
		ft_printf("syntax error near unexpected token `newline'\n");
}
