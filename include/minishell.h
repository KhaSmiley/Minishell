/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:48:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/26 22:52:59 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token t_token;

typedef struct s_token
{
    char *str;
    int type;
    struct s_token *next;
} t_token;

enum
{
    GREATER,
    DGREATER,
    LESS,
    DLESS,
    PIPE,
    SPACE,
    WORD
};

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

int ft_syntax(t_token *tok);
int ft_syntax_pipe(t_token *tok);
int ft_syntax_redir(t_token *tok);
int ft_syntax_word(t_token *tok);

#endif