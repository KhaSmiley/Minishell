/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:48:09 by kboulkri          #+#    #+#             */
/*   Updated: 2024/04/07 06:19:34 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_env	*env;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}					t_export;

typedef struct s_heredoc
{
	int				fd[2];
	char			*lim;
	int				in_cmd;
}					t_heredoc;

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
	char			*input;
	int				minishell_line_no;
	char			**envp_cpy;
	int				nb_hd;
	int				only_hd;
	int				tmp_fd;
	int				argc;
	int				count_tab;
	int				nb_cmd;
	int				pid[1024];
	int				pipe_fd[2];
	int				curr_here_doc;
	char			**builtin;
	char			**cmd;
	int				status;
	int				std_fd[2];
	t_export		*env_export;
}					t_data;

t_data				*simpleton(void);
extern int g_sig_return ;

/* syntax.c */

int					parsing_and_stock_input(char *input, t_token **tok,
						t_data *data);
int					ft_syntax(t_token **tok);
int					ft_syntax_pipe(t_token *tok);
int					ft_syntax_redir(t_token *tok);
int					ft_syntax_word(t_token *tok);

/* tokens.c */
int					ft_tokenizer(char *token);
int					alloc_token(t_token **tok, char *longchev, char *str,
						int i);
char				*isaword(char *str, int *i);
t_token				*find_token(char *str);

/* tokens_utils.c */

int					word_size(char *str, int i);
int					ft_find_end(char *str, char flag_quotes, int i);
char				*topositif(char *str);
char				*tonegatif(char *str);

/* expand.c */

void				ft_expand_str_y(t_token *tok, t_data *data);
char				*ft_find_value_env_new(char *str, int *i, t_data *data);
char				*double_quote(char *str, int *i, t_data *data);
char				*find_new_str_env_y(char *str, int *i, t_data *data);
char				*ft_get_new_str_for_env_y(char *str, t_data *data);

/* expand_utils_two.c */

int					ft_isalnum_env(int c);
int					ft_tablen(char **tab);
int					ft_find_malloc_key(char *str, int i);
char				*ft_find_key(char *str, int count);
char				*ft_find_value(char *key, t_export *env);

/* expand_utils_three.c */

int					ft_strlen_from_char(char *str, char c);
int					ft_strl(char *str);
int					ft_find_value_malloc(char *str, int *i);
char				*to_next_double_q(char *str, int *i);
int					is_last(char *str, int i);

/* expand_utils_four.c */

char				*normal(char *str, int *i);
char				*single_quote(char *str, int *i);
char				*ft_strjoin_you(char *s1, char *s2);

/* expand_after_quotes.c */

void				find_str_to_expand(t_token **tok);
// char					*ft_get_new_str_for_env(char *str, t_token *tok);
char				*ft_strjoin_env(char const *s1, char const *s2);

/* -------------------------- UTILS -------------------------- */

/* memory.c */

void				free_tok(t_token **tok);
void				free_envp_cpy(char **envp_cpy);
void				free_tok_env(t_env *my_env);
void				free_export(t_export *lst);

/* lst_utils.c */

void				print_list(t_token *lst);
t_token				*ft_lstnew(char *content, int type);
void				ft_stock(t_token **lst, t_token *new_link);
t_token				*ft_lstlast(t_token *lst);
void				free_list(t_token **tok);
int					ft_lstsize(t_export *env);

/* tab_utils.c */

void				free_tab(char **tab);
void				print_tab(char **tab);
char				**ft_envp_copy_to_tab(t_data *data);

/* signals.c */

void				handle_signals(void);
void				sigint_handler(int signum);
void				sigint_hd(int signum);

/* ------------------------- PARSING ------------------------- */

/* quotes.c */

void				del_char(char *address, char char_to_del);
int					remove_quotes(char *str);
int					manage_quote_errors(char *input);
t_token				*fix_quotes_token(t_token *tok);

/* quotes_utils.c */

int					check_closure(char *str, int i, char quote, int flag);
int					s_quotes_open(char *str);
int					d_quotes_open(char *str);
int					count_quotes(char *str, char c);
int					check_quotes_open(char *input);

/* --------------------- EXEC -------------------------------- */

/* pipex.c */

void				child_process(t_data *data, t_token **tok,
						t_heredoc *h_docs, int i);
int					exec_pipe(t_data *data, t_token **tok);
void				parent_process(t_data *data, int i);

/* redirections.c */

void				redirection(t_data *data, int i);
int					redir_files(t_token *tok, int i, t_heredoc *h_docs,
						t_data *data);
void				close_fds(t_data *data);
void				file_error(t_token *tok, t_data *data, char *str);

/* utils_exec_two.c */

char				*ft_strdup_access(char *cmd);
int					ft_strlen_from(int i, char *str);
int					open_fd(t_data *data, int i);

/* utils_exec.c */

char				*find_envp_path(t_export *env);
char				**split_path(t_data *data);
char				*complete_path(t_data *data, char *cmd);
void				init_data(int argc, t_data *data, t_token *tok);
int					ft_access(char *path);

/* exec_prep */

t_token				*find_curr_tok_pipe(t_token **tok, int nb_pipe);
int					ft_count_pipe(t_token *tok);
int					find_malloc_tok_to_tab(t_token **tok, int nb_pipe);
char				**tok_to_tab(t_token **tok, int nb_pipe);

/* exec_utils.c */

char				ft_get_last_char(const char *str);

/* here_doc.c */

void				write_hdocs(char *lim, int pipe, t_data *data);
void				exec_hdocs(t_heredoc *h_docs, t_data *data, int *i,
						t_token **tok);
void				close_heredocs(t_heredoc *h_docs, int limit);
int					find_heredoc(t_heredoc *h_docs, t_data *data, t_token *tmp);
t_heredoc			*here_doc_launch(t_data *data, t_token **tok);

/* here_doc_utils.c */

void				find_nb_hdoc(t_token *tok, t_data *data);
void				init_here_doc(t_heredoc *h_docs, t_token **tok,
						t_data *data);
void				ft_close_hd_child(t_data *data, t_heredoc *h_docs);

/* ------------------------- BUILT INS ------------------------ */

/*built_ins*/

int					lets_builtin(t_data *data, char **cmd, t_token **tok);
int					lets_builtin_no_fork(t_data *data, char **cmd,
						t_token **tok);
int					ft_pwd(void);
int					ft_cd(char **cmd, t_data *data);
int					ft_env(t_data *data);
int					ft_echo(char **cmd);
int					ft_exit_no_fork(char **args, t_data *data, t_token **tok);
int					ft_exit_fork(char **args, t_data *data, t_token **tok);

/* built_ins_utils.c */

int					to_builtin_or_not_to_builtin(char *cmd);
char				*find_first_cmd(t_token **tok);
int					one_built_in(char **builtin, t_token *tok, t_data *data);
int					check_echo_option(char **args, int i, int j);
char				*get_home_env(t_export *env);
void				clear_exit_no_fork(t_data *data, char **args,
						t_token **tok);

/* export */

void				ft_export(t_data *data, char **args);
void				ft_envp_copy_export(t_data *data, char **envp);
void				print_list_export(t_export *lst);

/* export_utils.c */

int					check_if_key_exist_export(t_export *lst, char *key);
void				free_key_export(void *delete);
char				*ft_find_key_export(char *str);
void				ft_delone_export(t_export **env, char *key);
void				ft_stock_export(t_export **lst, t_export *new_link);
t_export			*ft_lstnew_export(char *key, char *value);

/* unset.c */

void				ft_unset(t_data *data, char **args);

#endif
