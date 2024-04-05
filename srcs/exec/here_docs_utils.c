// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   here_docs_utils.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/02 02:28:11 by kboulkri          #+#    #+#             */
// /*   Updated: 2024/04/05 02:59:40 by kboulkri         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// t_heredoc *ft_lstlast_here_doc(t_heredoc *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// t_heredoc	*ft_lstnew_here_doc(int fd, char *content)
// {
// 	t_heredoc	*new;

// 	new = malloc(sizeof(*new));
// 	if (!new)
// 		return (NULL);
//     new->fd = fd;
// 	new->lim = content;
// 	new->next = NULL;
// 	return (new);
// }

// void	ft_stock_here_doc(t_heredoc **lst, t_heredoc *new_link)
// {
// 	if (!lst)
// 		return ;
// 	if (!*lst)
// 		*lst = new_link;
// 	else
// 		(ft_lstlast_here_doc(*lst))->next = new_link;
// }

// void print_list_here_doc(t_heredoc *lst)
// {
//     if (!lst)
// 		return ;
//     while(lst)
//     {
//         printf("string: %s\nin_cmd = %d\n", lst->lim, lst->in_cmd);
//         lst = lst->next;
//     }
//     return ;
// }

// int ft_lstsize_hdoc(t_heredoc *h_docs)
// {
// 	t_heredoc *tmp;
// 	int i;

// 	i = 0;
// 	if (!h_docs)
// 		return (i);
// 	tmp = h_docs;
// 	while(tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return(i);
// }
