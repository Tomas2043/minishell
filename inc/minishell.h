/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:54:08 by toandrad          #+#    #+#             */
/*   Updated: 2026/06/01 13:59:41 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <errno.h>
# include <sys/stat.h>

typedef struct s_heredoc
{
	int				fd[2];
	int				saved_stdin;
	struct termios	saved_term;
}	t_heredoc;

typedef struct s_pipe_info
{
	int	**pipes;
	int	i;
	int	n;
}	t_pipe_info;

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	int				quoted;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	int		running;
	char	*hd_hist;
	char	*hd_input;
	char	*hd_cmd;
	int		hd_hist_idx;
}	t_shell;

typedef struct s_es
{
	char	*result;
	int		sq;
	int		dq;
}	t_es;

typedef struct s_wlst
{
	char	**words;
	char	*cur;
	int		n;
	int		sq;
	int		dq;
	int		ws;
}	t_wlst;

extern volatile sig_atomic_t	g_signal;

// env
t_env	*init_env(char **envp);
char	*get_env(t_env *lst, char *key);
void	set_env(t_env **lst, char *key, char *value);
void	remove_env(t_env **lst, char *key);
char	**env_to_array(t_env *lst);
t_env	*new_env_node(char *key, char *value);
void	env_add_back(t_env **list, t_env *new_node);
int		count_env_size(t_env *lst);
void	free_env_array(char **env_array);
void	free_list(t_env *lst);

// path_resolution.c
char	*resolve_path(char *command, t_env *lst);
char	*search_in_paths(char **paths, char *command);

// redirections.c
int		apply_redirections(t_redir *lst, t_shell *shell);

// builtins
int		is_builtin(t_cmd *cmd);
void	builtin_env(t_shell *shell);
void	builtin_pwd(void);
void	builtin_echo(t_cmd *cmd);
void	builtin_exit(t_cmd *cmd, t_shell *shell);
void	builtin_cd(t_cmd *cmd, t_shell *shell);
void	builtin_export(t_cmd *cmd, t_shell *shell);
void	builtin_unset(t_cmd *cmd, t_shell *shell);
int		is_n_flag(char *str);
int		is_valid_identifier(char *str);
void	sort_env_array(char **array, int size);
char	**env_to_declare_array(t_env *lst);
void	print_export_err(char *name, t_shell *shell);

// executor
void	execute(t_cmd *cmd, t_shell *shell);
void	wait_child(pid_t pid, t_shell *shell);
void	child_execute(t_cmd *cmd, char *path, t_shell *shell);
void	pipeline_execute_external(t_cmd *cmd, t_shell *shell);
void	print_not_found_error(char *cmd);
void	dispatch_builtin(t_cmd *cmd, t_shell *shell, int builtin);

// heredoc.c
int		handle_heredoc(char *delimiter, t_shell *shell, int quoted);
int		prepare_heredocs(t_cmd *cmd, t_shell *shell);
void	close_prepared_heredocs(t_cmd *cmd);

// pipes
int		count_cmds(t_cmd *cmd);
void	free_pipes(int **pipes, int count);
void	close_pipe_fds(int **pipes, int count);
void	execute_pipeline(t_cmd *cmd, t_shell *shell);

// signals
void	setup_signals(void);
void	reset_signals(void);
void	setup_heredoc_signals(void);
void	handle_heredoc_sigint(int sig);
void	handle_wait_sigint(int sig);
void	setup_wait_signals(void);
void	setup_cont_signals(void);
int		cont_event_hook(void);

// utils
void	append_hd_hist(t_shell *shell, char *line);
void	update_hd_history(t_shell *shell);
int		ft_strcmp(char *s1, char *s2);
void	split_hd_input(char *line, t_shell *shell);
char	*next_hd_line(t_shell *shell);
char	*hd_readline(t_shell *shell);
char	*get_full_history_line(char *line);
void	handle_line(char **line, t_shell *shell);
void	process_hd_lines(t_shell *shell);
void	process_input_line(char *line, t_shell *shell);
void	restore_signals(void);
char	*cancel_cont(char *line, char *cont, t_shell *shell);
char	*append_cont_line(char *line, char *cont);
int		digit_overflow(char *str);

// tokenizer
size_t	count_tokens(const char *s);
int		handle_quote(char c, char *q);
int		escapable_quote(char c);
void	skip_word_chars(const char *s, size_t *i, char *q);
void	skip_token_op(const char *s, size_t *i);
size_t	word_len(const char *s, size_t i);
char	*get_op(const char *s, size_t *i);
void	free_split(char **arr);
int		is_space(char c);
int		is_op(char c);
char	*dup_str(const char *s, size_t len);
void	skip_spaces(const char *s, size_t *i);
char	**ms_tokenize(const char *s);

// syntax_check.c
int		check_syntax(t_token *tokens, char **bad);
char	find_unclosed_quote(const char *line);
int		has_trailing_pipe(const char *line);
void	print_syntax_error(char *bad);

// token_building.c
t_token	*build_token_list(char **split);

// expander
char	*expand_string(char *str, t_shell *shell);
void	expand_all(t_cmd *cmds, t_shell *shell);
int		update_quote_state(char c, int *sq, int *dq);
int		is_quoted_empty(char *str);
void	compact_empty_args(char **argv, int *keep);
char	*get_var(char *str, int *skip);
char	*expand_var(char *str, int *i, t_shell *shell);
char	**expand_to_wordlist(char *str, t_shell *shell);
int		expand_argv_count(t_cmd *cmd, t_shell *shell);
int		wl_init(t_wlst *s);
char	*wl_append(char *s, char c);
int		wl_add(t_wlst *s);
int		wl_dollar(char *str, int *i, t_wlst *s, t_shell *shell);

// parser
t_redir	*new_redir(t_redir_type type, char *filename, int quoted);
void	redir_add_back(t_redir **head, t_redir *node);
t_cmd	*parse_tokens(t_token *tokens);
int		fill_cmd(t_cmd *cmd, t_token **tok);
void	free_redir_list(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd);
void	free_tokens(t_token *tokens);

#endif
