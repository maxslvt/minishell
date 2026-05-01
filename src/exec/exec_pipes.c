#include "minishell.h"

void	handle_parent_process(int *input_fd, int pipe_fd[2], t_cmd *cur)
{
	ignore_signals();
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cur->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}