#include "minishell.h"

int	init_parsing(t_token *cur, int *error_code)
{
	if (error_code)
		*error_code = 0;
	if (cur && cur->type == PIPE)
	{
		if (error_code)
			*error_code = 2;
		pipe_error(NULL);
		return (0);
	}
	return (1);
}

int	process_cmd_token(t_cmd *new_cmd, t_token **cur, t_parse_info *info)
{
	if (!new_cmd || !parse_cmd_tokens(new_cmd, cur, info))
		return (0);
	return (1);
}


void	init_info(t_parse_info *info, t_var *env, int status, int *error_code)
{
	info->env = env;
	info->status = status;
	info->error_code = error_code;
}

int	handle_pipe(t_token **cur, int *error_code, t_cmd *cmd)
{
	if (*cur && (*cur)->type == PIPE)
	{
		*cur = (*cur)->next;
		if (!check_pipe_syntax(*cur, error_code))
		{
			pipe_error(cmd);
			return (0);
		}
	}
	return (1);
}
