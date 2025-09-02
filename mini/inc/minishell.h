/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:02:59 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:33:20 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define TOK_WS_SENTINEL 31

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_IN 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_HEREDOC 4
# define TOKEN_APPEND 5

# define PWD_ERR "pwd: error retrieving current \
	directory: getcwd : cannot access parent directories "

typedef struct s_token
{
	char				*value;
	int					type;
	int					quoted;
	struct s_token		*next;
}						t_token;

typedef struct s_redir	t_redir;
typedef struct s_cmd
{
	char				**argv;
	char				*infile;
	char				*outfile;
	char				*heredoc_delimiter;
	int					heredoc_quoted;
	int					append;
	int					pipe_fd[2];
	t_redir				*redirs;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_redir
{
	int					type;
	char				*file;
	int					append;
	int					quoted;
	struct s_redir		*next;
}						t_redir;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_malloc
{
	void				*content;
	struct s_malloc		*next;
}						t_malloc;

typedef struct s_shell
{
	char				*prompt;
	t_env				*env_list;
	char				**envp;
	t_token				*tokens;
	t_cmd				*cmds;
	int					exit_status;
	int					interactive;
	int					line_no;
	int					saved_stdin_fd;
	int					is_subshell;
}						t_shell;

typedef struct s_tokctx
{
	t_env				*env;
	t_shell				*shell;
	int					heredoc;
	int					*err;
	char				**res;
	int					*quoted;
}						t_tokctx;

typedef struct s_tokbuild
{
	t_token				**head;
	int					*heredoc_delim;
	t_shell				*shell;
	int					*err;
}						t_tokbuild;

t_token					*tokenize(const char *str, t_shell *shell, int *err);

int						tok_is_operator(char c);
int						tok_skip_spaces(const char *str, int i);
int						tok_get_token_type(const char *str, int i);
t_token					*tok_token_new(char *value, int type, int quoted);
void					tok_token_add_back(t_token **lst, t_token *new);
char					*tok_expand_word(const char *str, int *i,
							t_tokctx *ctx);

t_cmd					*parse_commands(t_token *tok, int *err);
t_cmd					*cmd_new(void);
int						is_redir(int type);
int						validate_syntax(t_token *tok);
void					add_redir(t_cmd *cmd, int type, const char *file);
void					add_heredoc_redir(t_cmd *cmd, const char *delim,
							int quoted);
int						is_builtin(const char *cmd);

void					*ft_malloc(size_t size);
void					ft_cleanup(t_malloc **m_list);

t_env					*copy_env(char **envp);
char					*expand_var(const char *str, int *i, t_env *env,
							int last_status);
char					*expand_line(const char *line, t_shell *shell);
void					display_env(t_env *env);
int						is_valid_var_name(const char *name);

int						builtin_echo(char **argv);
int						builtin_pwd(void);
int						builtin_cd(char **argv, t_env **env);
int						builtin_export(char **argv, t_env **env);
int						builtin_unset(char **argv, t_env **env);
int						builtin_env(t_env *env);
int						builtin_exit(char **argv, t_shell *shell);

int						child_process(t_cmd *cmd, t_env *env, char **envp,
							int in_fd);
int						wait_for_children(int n, int *status);
int						exec_external(t_cmd *cmd, t_env *env, char **envp);
int						execute_builtin(t_cmd *cmd, t_env **env,
							t_shell *shell);
int						execute_single_cmd(t_cmd *cmd, t_env **env, char **envp,
							t_shell *shell);
int						execute_pipeline(t_cmd *cmds, t_env **env, char **envp,
							t_shell *shell);
int						spawn_child(int prev_fd, int *pipe_fd, t_cmd *cur,
							t_shell *shell);
int						pipeline_loop(t_cmd *cmds, t_shell *shell);

void					restore_std_streams(int saved_out, int saved_in);
void					close_saved_streams(int saved_out, int saved_in);
int						is_exit_cmd(t_cmd *cmd);
int						return_with_reset(int ret, t_shell *shell);

char					*find_path(char *cmd, t_env *env);
char					**split_path_preserve_empty(const char *path);
int						validate_command_input(t_cmd *cmd);
int						check_path_permissions(const char *path);
void					print_command_not_found(const char *cmd_name);

int						run_single_builtin(t_cmd *cmd, t_env **env,
							t_shell *shell, int saved_stdin);
int						handle_empty_command(t_cmd *cmd, int saved_stdin);
int						run_external_single(t_cmd *cmd, t_env **env,
							char **envp, int saved_stdin);

int						open_pipe(int pipe_fd[2]);
void					close_pipe(int pipe_fd[2]);

int						redirect_input(const char *file);
int						redirect_output(const char *file, int append);
int						apply_all_redirs(t_cmd *cmd);
int						handle_heredoc_execution(const char *delimiter,
							int quoted, t_shell *shell);

void					setup_signals(void);
void					setup_heredoc_signals(void);

extern int				g_signal;

int						prep_heredoc(t_cmd *cmd, t_shell *shell,
							int *saved_stdin);

void					init_shell(t_shell *shell, char **envp);
// char					*get_input(t_shell *shell, char *prompt);
int						process_line(t_shell *shell, char *line);
void					cleanup_after_command(t_shell *shell);
char					*tok_str_append_char(char *acc, char c);
char					*tok_expand_inner(const char *s, t_env *env,
							t_shell *shell);
char					*tok_env_value_for_key(t_env *env, const char *key);
char					*tok_handle_env(const char *str, int *i, t_env *env,
							t_shell *shell);
int						find_closing_quote(const char *str, int start,
							char quote);
char					*handle_quote_expansion(char *content, char quote,
							t_tokctx *ctx);
void					protect_whitespace(char *content);
char					*tok_handle_quotes(const char *str, int *i,
							t_tokctx *ctx);
int						join_part(char **res, char *part);
char					*tok_handle_env(const char *str, int *i, t_env *env,
							t_shell *shell);
int						process_heredoc_expansion(char **value, t_tokbuild *tb,
							int quoted);
void					setup_token_context(t_tokctx *ctx, t_tokbuild *tb,
							int *quoted);
int						add_splitted_tokens(char *value, t_token **head);
void					restore_ws(char *s);
int						handle_operator_token(const char *str, int *i,
							t_token **head, int *heredoc_delim);
int						count_cmd_args(t_token *tok);
t_cmd					*append_new_cmd(t_cmd **head, t_cmd *cur);
t_shell					*store_shell(t_shell *shell);
void					heredoc_child_loop(int wfd, const char *delim,
							int quoted, t_shell *shell);
int						process_heredoc_line(char **line, const char *delim,
							int quoted, int wfd);
void					handle_heredoc_eof(int wfd, const char *delim,
							t_shell *shell);
char					*read_heredoc_line(t_shell *shell);
int						process_heredoc_redirs(t_redir *it, int saved_stdin,
							t_shell *shell);
int						process_cmd_heredoc(t_cmd *cmd, int saved_stdin,
							t_shell *shell);
char					*find_equals_in_entry(const char *entry);
void					set_env_key_value(t_env *new, const char *entry,
							char *eq);
void					create_new_env(t_env **env, const char *key,
							const char *val);

void					update_existing_env(t_env *var, const char *val,
							int append);
void					display_exports(t_env *env);
void					sort_env_ptrs(t_env **arr, int n);
int						count_env(t_env *env);
t_env					*find_env(t_env *env, const char *key);

void					ft_exit(int status);

#endif
