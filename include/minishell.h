/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:48:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/04 17:43:37 by lbarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token	t_token;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
}						t_token;

enum
{
	GREATER,
	DGREATER,
	LESS,
	DLESS,
	PIPE,
	WHITE_SPACE,
	WORD,
};

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* expand.c */

void					ft_expand(char **envp);
char					**ft_cpy_envp(char **envp);
char					*ft_find_var(char *var, char **envp_cpy);
int						ft_strlen_from_char(char *str, char c);
void					free_tab(char **tab);

/* expand_utils.c */

char					*expand_new_str(char *str, char *key, char *value);

/* lst_utils.c */

void					print_list(t_token *lst);
t_token					*ft_lstnew(char *content, int type);
void					ft_stock(t_token **lst, t_token *new_link);
t_token					*ft_lstlast(t_token *lst);

/* quotes.c */

// int					ft_check_open_d_quotes(char *str);
// int					ft_check_open_s_quotes(char *str);
void					del_char(char *address, char char_to_del);
int						remove_quotes(char *str, char quote);
int						count_quotes(char *str, char c);
int						manage_quotes(char *str);
int						in_d_quotes(char *str);
int						in_s_quotes(char *str);

/* syntax.c */

int						ft_syntax(t_token *tok);
int						ft_syntax_pipe(t_token *tok);
int						ft_syntax_redir(t_token *tok);
int						ft_syntax_word(t_token *tok);

#endif
