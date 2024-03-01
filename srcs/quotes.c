/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:00:56 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/01 02:54:51 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_open_d_quotes(char *str)
{
	int	i;
    int quotes_flag;

	i = 0;
    quotes_flag = 0;
	while (str[i])
	{
		if (str[i] == '"')
        {
            quotes_flag = 1 - quotes_flag;
            i++;
        }
        else
            i++;
	}
    if (quotes_flag == 1)
        return (1);
    return (0);
}

int	ft_check_open_s_quotes(char *str)
{
	int	i;
    int quotes_flag;

	i = 0;
    quotes_flag = 0;
	while (str[i])
	{
		if (str[i] == 39)
        {
            quotes_flag = 1 - quotes_flag;
            i++;
        }
        else
            i++;
	}
    if (quotes_flag == 1)
        return (1);
    return (0);
}