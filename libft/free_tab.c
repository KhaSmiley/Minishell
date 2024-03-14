/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:08:15 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/13 23:37:33 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void free_tab(char **tab)
{
    int i;

    i = 0;
	if (!tab || !*tab)
		return ;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
	free(tab);
}
