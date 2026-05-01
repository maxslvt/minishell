#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <stdbool.h>
# include <signal.h>

# define WORD 0
# define REDIR_IN 1			// <
# define REDIR_OUT 2		// >
# define REDIR_APPEND 3		// >>
# define HEREDOC 4			// <<
# define PIPE 5				// |
# define REDIR_RDWR 6		// <>

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

typedef struct s_redirect
{
	int					type;
	int					is_heredoc;
	int					expand_heredoc;
	char				*files;
	char				*eof;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**cmd;
	int				nb_redirect;
	t_redirect		*redirect;
	int				*infile;
	int				outfile;
	int				code;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_tok_list
{
	t_token	*head;
	t_token	*tail;
}	t_tok_list;

typedef struct s_parse_info
{
	t_var	*env;
	int		status;
	int		*error_code;
}	t_parse_info;

/* GLOBAL */
extern volatile sig_atomic_t	g_sig;

/* PARSING & SETUP */
t_cmd	*cmd_new(char **argv, int *infile_fd, int outfile_fd);
int		get_token_len(char *str);
int		check_quote(char *str);
int		is_whitespace(char c);
int		is_special(char c);
void	free_token_list(t_token *head);
char	*extract_quoted(char *str, int len);
int		handle_backslash(char *res, int *i, char *str, int *j);
t_token	*tokenize_line(char *line);
t_cmd	*parsing(t_token *head, t_var *env, int status, int *error_code);
int		pipe_error(t_cmd *cmd);
int		assign_type(char *str);
void	add_arg(t_cmd *new_cmd, char *value);
char	*remove_quotes(char *str);
int		add_redirect(t_cmd *new_cmd, t_token *cur, t_var *env, int status);
t_redirect	*create_redirect(t_token *cur, t_var *env, int status);
t_cmd	*init_cmd(void);
void	add_cmd_to_list(t_cmd **cmd, t_cmd **tmp, t_cmd *new_cmd);
bool	add_token(char *value, int type, t_tok_list *list);
t_token	*create_token(char *value, int type);
char	*ft_expand(char *str, t_var *env, int status);

/* EXECUTION */
int		execute_pipeline(t_cmd *cmd_list, t_var **env_list, int last_status);
int		process_heredocs(t_cmd *cmd_list, t_var *env, int status);
int		process_heredoc_line(int pipefd, t_redirect *redir, char *line,
			t_var *env);
void	handle_parent_process(int *input_fd, int pipe_fd[2], t_cmd *cur);
int		read_heredoc_lines(int pipefd[2], t_redirect *redir, t_var *env);
void	cleanup_and_exit(t_cmd *cmd, t_var **env, int exit_code);
void	setup_child_pipes(int in_fd, t_cmd *cmd, int pipe_fd[2]);
int		try_to_wait(int pid, int *exit_status);
int		wait_for_children(pid_t last_pid);

/* PROCESS MANAGEMENT */
void	exec_external_cmd(t_cmd *cmd, t_var **env_list);

/* BUILTINS */
int		is_builtin(char *cmd_name);
int		exec_builtin(t_cmd *cmd, t_var **env_list, int last_status);
int		ft_cd(t_cmd *cmd, t_var **env_list);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_var *env);
int		is_valid_env_var(char *str);
int		ft_exit(t_cmd *cmd, t_var **env, int last_status);
int		ft_export(t_cmd *cmd, t_var **env_list);
int		check_option(char *arg, int *end_opt);
int		valid_name(char *str);
void	err_export(char *name);
int		ft_varsize(t_var *env);
t_var	*find_var(t_var *env, char *name);
int		parse_export_arg(char *arg, char **name, char **value);
int		ft_pwd(t_cmd *cmd);
int		ft_unset(t_cmd *cmd, t_var **env_list);
int		dispatch_builtin(t_cmd *cmd, t_var **env_list, int last_status);

/* REDIRECTIONS */
int		apply_redirections(t_cmd *cmd);
void	restore_fds(int original_stdin, int original_stdout);
int		check_redir_syntax(t_token *next);
int		process_redir(t_cmd *new_cmd, t_token **cur, t_parse_info *info);
int		process_cmd_token(t_cmd *new_cmd, t_token **cur, t_parse_info *info);
int		check_pipe_syntax(t_token *cur, int *error_code);
int		handle_pipe(t_token **cur, int *error_code, t_cmd *cmd);
int		init_parsing(t_token *cur, int *error_code);
int		parse_cmd_tokens(t_cmd *new_cmd, t_token **cur, t_parse_info *info);
/* ENVIRONMENT & PATH */
t_var	*create_env(char **envp);
t_var	*new_var(char *envp_line);
char	**convert_env_list(t_var *list);
char	*get_env_value(char *name, t_var *env_list);
char	*find_cmd_path(char *cmd, t_var *env_list);

/* UTILS & MEMORY */
void	append_redirect(t_cmd *cmd, t_redirect *redir);
void	ft_free_exit(t_cmd *cmd, t_var **env, int last_status);
void	ft_free_tab(char **tab);
void	ft_free_env(t_var *env);
void	ft_free_cmd(t_cmd *c);
void	ft_free_cmd_list(t_cmd *list);
int		ft_strcmp(const char *s1, const char *s2);
int		err_msg(const char *pfx, const char *msg, int code);
void	free_and_null(t_tok_list *list);
void	setup_signal_handlers(void);
void	ignore_signals(void);
void	restore_signals(void);
void	setup_heredoc_signals(void);
int		has_quotes(char *str);
int		is_ambiguous(char *str);
void	init_info(t_parse_info *info, t_var *env, int status, int *error_code);
char	*ft_chrdup(char c);

#endif