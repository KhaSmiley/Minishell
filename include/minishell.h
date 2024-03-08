/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:48:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/08 22:02:10 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token	t_token;

// struct for the token list and a new struct to add the key + value for each $ found in word

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
	struct s_env		*env;
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

char					*ft_find_value(char *key, char **envp_cpy);
int					ft_create_env(t_token *tok, char *str,
							char **envp_cpy);
void					ft_expand_str(t_token *tok, char **envp_cpy);

/* expand_new.c */

t_env	*ft_create_env_new(t_token *tok, char *str);
void					ft_expand_dollar(t_token *tok_word);

/* expand_utils.c */

t_env					*ft_lstnew_env(char *key, char *value);
void					ft_stock_env(t_env **lst, t_env *new_link);
void					print_list_env(t_token *lst);

/* expand_utils_two */

int						ft_find_malloc_key(char *str, int i);
char					*ft_find_key(char *str, int y);
int						ft_strlen_from_char(char *str, char c);
char					**ft_envp_copy(char **envp);
int						ft_tablen(char **tab);

/* lst_utils.c */

void					print_list(t_token *lst);
t_token					*ft_lstnew(char *content, int type);
void					ft_stock(t_token **lst, t_token *new_link);
t_token					*ft_lstlast(t_token *lst);

/* quotes.c */

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
int						ft_tokenizer(char *token);
int						word_size(char *str, int i);
int						alloc_token(t_token **tok, char *longchev, char *str,
							int i);
t_token					*find_token(char *str);

#endif
