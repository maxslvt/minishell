#include "minishell.h"

static void	execute_child(t_cmd *cmd, t_var **env, int in_fd, int pipe_fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	setup_child_pipes(in_fd, cmd, pipe_fd);
	if (apply_redirections(cmd) != 0)
		cleanup_and_exit(cmd, env, 1);
	if (!cmd->cmd || !cmd->cmd[0])
		cleanup_and_exit(cmd, env, 0);
	if (is_builtin(cmd->cmd[0]))
		exit(exec_builtin(cmd, env, 0));
	else
		exec_external_cmd(cmd, env);
}

static int	exec_builtin_with_redir(t_cmd *cmd, t_var **env, int status)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(cmd) != 0)
		ret = 1;
	else if (!cmd->cmd || !cmd->cmd[0])
		ret = 0;
	else
		ret = dispatch_builtin(cmd, env, status);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (ret);
}

static pid_t	process_pipeline_cmd(t_cmd *current, t_var **env_list,
	int *input_fd, int pipe_fd[2])
{
	pid_t	pid;

	if (current->next)
		pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		execute_child(current, env_list, *input_fd, pipe_fd);
	else if (pid > 0)
		handle_parent_process(input_fd, pipe_fd, current);
	return (pid);
}

int	execute_pipeline(t_cmd *cmd_list, t_var **env_list, int last_status)
{
	int		pipe_fd[2];
	int		input_fd;
	t_cmd	*current;
	int		exit_status;
	pid_t	last_pid;

	if (!cmd_list->next && (!cmd_list->cmd || !cmd_list->cmd[0]))
		return (exec_builtin_with_redir(cmd_list, env_list, last_status));
	if (!cmd_list->next && is_builtin(cmd_list->cmd[0]))
		return (exec_builtin_with_redir(cmd_list, env_list, last_status));
	input_fd = STDIN_FILENO;
	current = cmd_list;
	while (current)
	{
		last_pid = process_pipeline_cmd(current, env_list, &input_fd, pipe_fd);
		current = current->next;
	}
	exit_status = wait_for_children(last_pid);
	restore_signals();
	return (exit_status);
}