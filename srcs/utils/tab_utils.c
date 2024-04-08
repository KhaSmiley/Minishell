/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:23:47 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/08 03:49:24 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_envp_copy_to_tab(t_data *data)
{
	t_export	*tmp;
	char		*new_str;
	char		**tab;
	int			size;
	int			i;

	i = 0;
	tmp = data->env_export;
	size = ft_lstsize(data->env_export);
	tab = NULL;
	tab = malloc(sizeof(char *) * (size + 1));
	while (tmp)
	{
		new_str = NULL;
		new_str = ft_strjoin(tmp->key, "=");
		new_str = ft_strjoin_gnl(new_str, tmp->value);
		tab[i] = ft_strdup(new_str);
		free(new_str);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
