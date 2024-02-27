/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/27 03:08:27 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char *ft_stock_token(char *str)
// {
//     int i;

//     i = 0;
//     if (str[i] == LESS)
// }

// int ft_count_new(char *str)
// {
//     int i;
//     int count;

//     i = 0;
//     count = 0;
//     while(str[i])
//     {
//         if (str[i] == '<' && str[i + 1] == '<')
//         {
//             count+= 3;
//             i++;
//         }    
//         else if (str[i] == '>' && str[i + 1] == '>')
//         {
//             count+= 3;
//             i++;
//         }
//         else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
//             count += 2;
//         i++;
//         count++;
//     }
//     return (count);
// }

// char     *ft_tokenizer(char *token)
// {
//     if (token == "<")
//         return ("LESS");
//     else if (token == ">")
//         return ("GREATER");
//     else if (token == "<<")
//         return ("DLESS");
//     else if (token == ">>")
//         return ("DGREATER");
//     else if (token == "|")
//         return ("PIPE");
//     else if (token == " ")
//         return ("SPACE");
//     else
//         return ("WORD");
// } 

t_token *ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_stock(t_token **lst, t_token *new_link)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new_link;
	else
		(ft_lstlast(*lst))->next = new_link;
}

t_token	*ft_lstnew(char *content, int type)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->str = content;
    new->type = type;
	new->next = NULL;
	return (new);
}

int     ft_tokenizer(char *token)
{
    if (strcmp(token, "<") == 0)
        return (LESS);
    else if (strcmp(token, ">") == 0)
        return (GREATER);
    else if (strcmp(token, "<<") == 0)
        return (DLESS);
    else if (strcmp(token, ">>") == 0)
        return (DGREATER);
    else if (strcmp(token, "|") == 0)
        return (PIPE);
    else if (strcmp(token, " ") == 0)
        return (SPACE);
    else
        return (WORD);
} 

void print_list(t_token *lst)
{
    if (!lst)
        return ;
    while(lst)
    {
        printf("WORD : %s TYPE : %d\n", lst->str, lst->type);
        lst = lst->next;
    }
    return ;
}

int taille_mot(char *str, int i)
{
    int j;

    j = 0;
    while(str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\0')
    {
        j++;
        i++;
    }
    return (j);
}   

int    alloc_token(t_token *tok, char *longchev, char *str, int i)
{
    if (str[i + 1] == longchev[0])
    {
        ft_stock(&tok, ft_lstnew(longchev, ft_tokenizer(longchev)));
        return (1);
    }
    ft_stock(&tok, ft_lstnew(&longchev[1], ft_tokenizer(&longchev[1])));  
    return (0);
}


void    find_token(char *str)
{
    int i;
    int j;
    char *word;
    t_token *tok;
    
    tok = NULL;
    // word = malloc(sizeof(char) * 100);
    i = 0;
    while(str[i])
    {
        if (str[i] == '<')
            i += alloc_token(tok, "<<", str, i);
        else if (str[i] == '>')
            i += alloc_token(tok, ">>", str, i);
        else if (str[i] == '|')
            ft_stock(&tok, ft_lstnew("|", ft_tokenizer("|")));
        else if (str[i] == ' ')
            ft_tokenizer(" ");
        else
        {
            j = 0;
            word = malloc(taille_mot(str, i) + 1);
            while (strchr(" \t><|\0", str[i]) == 0) // ft_
                word[j++] = str[i++];
            word[j] = '\0';
            ft_stock(&tok, ft_lstnew(word, ft_tokenizer(word)));
            i--;
        }
        i++;
    }
    print_list(tok);
    ft_syntax(tok);
    // while(tok)
    // {
    //     t_token *tmp;
    //     tmp = tok;
    //     printf("WORD : %s TYPE : %d\n", tok->str, tok->type);
    //     tok = tok->next;
    //     free(tmp);
    // }
    return ;
}   

int main(int argc, char **argv, char **envp)
{
    t_token lst;

    while (1)
    {
        char *input = readline("> ");
        if (!input)
            break;
        if (!*input)
            continue;
        add_history(input);
        find_token(input);
    }
    return (0);
}