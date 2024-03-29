/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:48:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/29 04:43:02 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token	t_token;

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

typedef struct s_export
{
	char				*key;
	char				*value;
	struct s_export		*next;
}						t_export;

typedef struct s_heredoc
{
	int					fd;
	char				*lim;
	int					in_cmd;
	struct s_heredoc	*next;
}						t_heredoc;

enum
{
	GREATER,
	DGREATER,
	LESS,
	DLESS,
	PIPE,
	WHITE_SPACE,
	WORD,
	EMPTY,
};

typedef struct s_data
{
	char				*input;
	char				**envp_cpy;
	int					tmp_fd;
	int					argc;
	int					count_tab;
	int					nb_cmd;
	int					pid[1024];
	int					pipe_fd[2];
	int					curr_here_doc;
	t_export			*env_export;
}						t_data;

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/* expand.c */

char					*ft_find_value(char *key, t_export *env);
int						ft_create_env(t_token *tok, char *str, t_export *env);
void					ft_expand_str(t_token *tok, t_data *data);
void					check_quotes_for_env(char *quote_char, char *word,
							int i_word);

/* expand_utils.c */

t_env					*ft_lstlast_env(t_env *lst);
void					ft_stock_env(t_env **lst, t_env *new_link);
t_env					*ft_lstnew_env(char *key, char *value);
void					print_list_env(t_token *lst);
void					free_list_env(t_env *tok);

/* expand_utils_two.c */

char					*ft_find_key(char *str, int count);
int						ft_strlen_from_char(char *str, char c);
int						ft_find_malloc_key(char *str, int i);
int						ft_tablen(char **tab);
char					**ft_envp_copy(char **envp);
int						ft_isalnum_env(int c);

/* expand_after_quotes.c */

void					find_str_to_expand(t_token **tok);
char					*ft_get_new_str_for_env(char *str, t_token *tok);
char					*ft_strjoin_env(char const *s1, char const *s2);

/* lst_utils.c */

void					print_list(t_token *lst);
t_token					*ft_lstnew(char *content, int type);
void					ft_stock(t_token **lst, t_token *new_link);
t_token					*ft_lstlast(t_token *lst);
void					free_list(t_token **tok);

/* quotes.c */

void					del_char(char *address, char char_to_del);
int						remove_quotes(char *str);
int						manage_quote_errors(char *input);
t_token					*fix_quotes_token(t_token *tok);

/* quotes_utils.c */

int						check_closure(char *str, int i, char quote, int flag);
int						s_quotes_open(char *str);
int						d_quotes_open(char *str);
int						count_quotes(char *str, char c);
int						check_quotes_open(char *input);

/* syntax.c */

int						ft_syntax(t_token **tok);
int						ft_syntax_pipe(t_token *tok);
int						ft_syntax_redir(t_token *tok);
int						ft_syntax_word(t_token *tok);
int						ft_tokenizer(char *token);
int						word_size(char *str, int i);
int						alloc_token(t_token **tok, char *longchev, char *str,
							int i);
t_token					*find_token(char *str);

/* memory.c */

void					free_tok(t_token **tok);
void					free_envp_cpy(char **envp_cpy);
void					free_tok_env(t_env *my_env);
void					free_export(t_export *lst);

/* ------------------------------------------------------------------- EXEC -------------------------------------------------------------------------- */

/* tab_utils.c */

void					free_tab(char **tab);
void					print_tab(char **tab);

/* pipex.c */

void					child_process(t_data *data, t_token **tok, int i);
int						exec_pipe(t_data *data, t_token **tok);
void					redirection(t_data *data, int i);
void					parent_process(t_data *data, int i);
void					close_fds(t_data *data);

/* utils_exec_two.c */

char					*ft_strdup_access(char *cmd);
int						ft_strlen_from(int i, char *str);
int						open_fd(t_data *data, int i);

/* utils_exec.c */

char					*find_envp_path(char **envp);
char					**split_path(t_data *data);
char					*complete_path(t_data *data, char *cmd);
void					init_data(int argc, t_data *data, t_token *tok);
int						ft_access(char *path);

/* tok_to_tab */

char					**tok_to_tab(t_token **tok, int nb_pipe);
int						ft_count_pipe(t_token *tok);

/*built_ins*/

int						to_builtin_or_not_to_builtin(char *cmd);
int						lets_builtin(t_data *data, char **cmd, char **envp_cpy);
char					*find_first_cmd(t_token **tok);
int						one_built_in(char **builtin, t_data *data);
int						ft_pwd(void);
int						ft_cd(char **cmd, char **env_cpy);
int						ft_env(t_data *data);
int						ft_echo(char **cmd);

/* export */

void					ft_export(t_data *data, char **args);
void					ft_envp_copy_export(t_data *data);
void					print_list_export(t_export *lst);

/* export_utils.c */

int						check_if_key_exist_export(t_export *lst, char *key);
void					free_key_export(void *delete);
char					*ft_find_key_export(char *str);
void					ft_delone_export(t_export **env, char *key);
void					ft_stock_export(t_export **lst, t_export *new_link);
t_export				*ft_lstnew_export(char *key, char *value);

/* unset.c */
void					ft_unset(t_data *data, char **args);

/* here_doc.c */

t_heredoc				*exec_here_docs(t_data *data, t_token **tok);
void					print_list_here_doc(t_heredoc *lst);

#endif