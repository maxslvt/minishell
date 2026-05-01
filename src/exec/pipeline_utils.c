#include "minishell.h"

void	cleanup_and_exit(t_cmd *cmd, t_var **env, int exit_code)
{
	cmd->next = NULL;
	ft_free_cmd(cmd);
	ft_free_env(*env);
	exit(exit_code);
}

void	setup_child_pipes(int in_fd, t_cmd *cmd, int pipe_fd[2])
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

int	try_to_wait(int pid, int *exit_status)
{
	int	tries_count;
	int	ret;

	tries_count = 0;
	while (tries_count < 10)
	{
		ret = waitpid(pid, exit_status, 0);
		if (ret != -1)
			return (ret);
		else if (errno == EINTR)
			tries_count++;
		else
			return (-1);
	}
	return (-1);
}

static int	handle_child_status(int wstatus)
{
	int	exit_status;

	exit_status = 0;
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		exit_status = 128 + WTERMSIG(wstatus);
		if (WTERMSIG(wstatus) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(wstatus) == SIGINT)
			write(2, "\n", 1);
	}
	return (exit_status);
}

int	wait_for_children(pid_t last_pid)
{
	int		wstatus;
	int		exit_status;
	pid_t	pid;

	exit_status = 0;
	while (1)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (pid == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (pid == last_pid)
			exit_status = handle_child_status(wstatus);
	}
	return (exit_status);
}