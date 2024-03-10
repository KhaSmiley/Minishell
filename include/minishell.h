/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarry <lbarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:48:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/10 01:28:33 by lbarry           ###   ########.fr       */
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

typedef struct s_input
{
	int	dollar_flag;
}				t_input;

enum
{
	GREATER,
	DGREATER,
	LESS,
	DLESS,
	PIPE,
	WHITE_SPACE,
	DOLLAR,
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

/* quotes_utils.c */

int						check_closure(char *str, int i, char quote, int flag);
int						s_quotes_open(char *str);
int						d_quotes_open(char *str);
int						count_quotes(char *str, char c);
int						check_solo_quotes_open(char *input);
int						check_quotes_open(char *input);

/* quotes.c */

void					del_char(char *address, char char_to_del);
int						remove_quotes(char *str, char quote);
int						manage_quotes(char *str);
char					find_next_quote(char *str);
int						manage_solo_quotes(char *str);
int						manage_quotes(char *input);

/* syntax.c */

int						ft_syntax(t_token *tok);
int						ft_syntax_pipe(t_token *tok);
int						ft_syntax_redir(t_token *tok);
int						ft_syntax_word(t_token *tok);
int						ft_tokenizer(char *token);
int						word_size(char *str, int i);
int						alloc_token(t_token **tok, char *longchev, char *str, int i);
void					find_token(char *str);

#endif
