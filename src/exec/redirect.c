#include "minishell.h"

static int	handle_output(t_redirect *redir)
{
	int	fd;
	int	flags;

	if (redir->type == REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(redir->files, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->files);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_input(t_cmd *cmd, t_redirect *redir)
{
	int	fd;

	if (redir->is_heredoc)
	{
		if (cmd->infile && *cmd->infile != -1)
		{
			dup2(*cmd->infile, STDIN_FILENO);
			close(*cmd->infile);
			return (0);
		}
		return (1);
	}
	fd = open(redir->files, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->files);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redirect	*cur;

	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == REDIR_OUT || cur->type == REDIR_APPEND)
		{
			if (handle_output(cur) != 0)
				return (1);
		}
		else if (cur->type == REDIR_IN || cur->is_heredoc)
		{
			if (handle_input(cmd, cur) != 0)
				return (1);
		}
		cur = cur->next;
	}
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
	return (0);
}

void	restore_fds(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}