/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:54:08 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/16 11:39:00 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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
}	t_shell;

// env_init.c 
t_env	*init_env(char **envp);

// env_helpers.c
char	*get_env(t_env *lst, char *key);
void	set_env(t_env **lst, char *key, char *value);
void	remove_env(t_env **lst, char *key);
char	**env_to_array(t_env *lst);

// env_utils.c
t_env	*new_env_node(char *key, char *value);
void	env_add_back(t_env **list, t_env *new_node);
int		count_env_size(t_env *lst);
void	free_env_array(char **env_array);
void	free_list(t_env *lst);

// path_resolution.c
char	*resolve_path(char *command, t_env *lst);
char	*search_in_paths(char **paths, char *command);

// redirections.c
void	apply_redirections(t_redir *lst);

// builtins.c & builtins2.c
int		is_builtin(t_cmd *cmd);
void	builtin_env(t_shell *shell);
void	builtin_pwd(void);
void	builtin_echo(t_cmd *cmd);
void	builtin_exit(t_cmd *cmd, t_shell *shell);
void	builtin_cd(t_cmd *cmd, t_shell *shell);
void	builtin_export(t_cmd *cmd, t_shell *shell);
void	builtin_unset(t_cmd *cmd, t_shell *shell);

// executor.c
void	execute(t_cmd *cmd, t_shell *shell);

// executor_helpers.c
void	wait_child(pid_t pid, t_shell *shell);
void	child_execute(t_cmd *cmd, char *path, t_shell *shell);

// pipes.c
void	execute_pipeline(t_cmd *cmd, t_shell *shell);

// pipe_helpers.c
int		count_cmds(t_cmd *cmd);
void	free_pipes(int **pipes, int count);

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
int		ft_strcmp(char *s1, char *s2);
int		check_syntax(t_token *tokens);
t_token	*build_token_list(char **split);

char	*expand_string(char *str, t_shell *shell);
void	expand_tokens(t_token *tokens, t_shell *shell);
void	expand_all(t_cmd *cmds, t_shell *shell);

#endif
