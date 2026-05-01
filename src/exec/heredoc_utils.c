#include "minishell.h"

static int	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (0);
}

int	process_heredoc_line(int pipefd, t_redirect *redir, char *line,
	t_var *env)
{
	char	*expanded;

	if (redir->expand_heredoc)
	{
		expanded = ft_expand(line, env, 0);
		free(line);
		if (!expanded)
			return (-1);
		write_heredoc_line(pipefd, expanded);
		free(expanded);
	}
	else
	{
		write_heredoc_line(pipefd, line);
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_redirect *redir, t_cmd *cmd, t_var *env, int status)
{
	int		pipefd[2];
	int		ret;

	(void)status;
	if (pipe(pipefd) == -1)
		return (-1);
	setup_heredoc_signals();
	ret = read_heredoc_lines(pipefd, redir, env);
	restore_signals();
	if (ret == -1)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	close(pipefd[1]);
	if (cmd->infile && *cmd->infile != -1)
		close(*cmd->infile);
	if (!cmd->infile)
	{
		cmd->infile = malloc(sizeof(int));
		if (!cmd->infile)
			return (-1);
	}
	*cmd->infile = pipefd[0];
	return (0);
}

int	process_heredocs(t_cmd *cmd_list, t_var *env, int status)
{
	t_cmd		*current;
	t_redirect	*redir;

	current = cmd_list;
	while (current)
	{
		redir = current->redirect;
		while (redir)
		{
			if (redir->is_heredoc)
			{
				if (handle_heredoc(redir, current, env, status) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}