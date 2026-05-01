#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0 || ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0 || ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0 || ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0
		|| is_valid_env_var(cmd_name) == 0 || ft_strcmp(cmd_name, ":") == 0)
		return (1);
	return (0);
}

int	dispatch_builtin(t_cmd *cmd, t_var **env_list, int last_status)
{
	char	*name;

	name = cmd->cmd[0];
	if (ft_strcmp(name, ":") == 0)
		return (0);
	if (is_valid_env_var(name) == 0)
		return (0);
	if (ft_strcmp(name, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(name, "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(name, "env") == 0)
		return (ft_env(*env_list));
	if (ft_strcmp(name, "export") == 0)
		return (ft_export(cmd, env_list));
	if (ft_strcmp(name, "cd") == 0)
		return (ft_cd(cmd, env_list));
	if (ft_strcmp(name, "unset") == 0)
		return (ft_unset(cmd, env_list));
	if (ft_strcmp(name, "exit") == 0)
		return (ft_exit(cmd, env_list, last_status));
	return (127);
}

int	exec_builtin(t_cmd *cmd, t_var **env_list, int last_status)
{
	int	original_stdin;
	int	original_stdout;
	int	status;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(cmd) != 0)
	{
		restore_fds(original_stdin, original_stdout);
		return (1);
	}
	status = dispatch_builtin(cmd, env_list, last_status);
	restore_fds(original_stdin, original_stdout);
	return (status);
}