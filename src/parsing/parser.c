#include "minishell.h"

static int	process_word(t_cmd *cmd, t_token *cur, t_var *env, int status)
{
	char	*expanded;
	char	*clean;
	char	*quote;

	quote = ft_strchr(cur->value, '"');
	expanded = ft_expand(cur->value, env, status);
	if (!expanded)
		return (0);
	clean = remove_quotes(expanded);
	free(expanded);
	if (!clean)
		return (0);
	if (clean[0] != '\0' || quote)
		add_arg(cmd, clean);
	free(clean);
	return (1);
}

int	parse_cmd_tokens(t_cmd *new_cmd, t_token **cur, t_parse_info *info)
{
	while (*cur && (*cur)->type != PIPE)
	{
		if ((*cur)->type == WORD)
		{
			if (!process_word(new_cmd, *cur, info->env, info->status))
				return (0);
		}
		else if ((*cur)->type == REDIR_IN || (*cur)->type == REDIR_OUT
			|| (*cur)->type == HEREDOC || (*cur)->type == REDIR_APPEND
			|| (*cur)->type == REDIR_RDWR)
		{
			if (!process_redir(new_cmd, cur, info))
				return (0);
		}
		*cur = (*cur)->next;
	}
	return (1);
}

t_cmd	*parsing(t_token *head, t_var *env, int status, int *error_code)
{
	t_cmd			*cmd;
	t_cmd			*tail;
	t_cmd			*new_cmd;
	t_parse_info	info;

	tail = NULL;
	cmd = NULL;
	init_info(&info, env, status, error_code);
	if (!init_parsing(head, error_code))
		return (NULL);
	while (head)
	{
		new_cmd = init_cmd();
		if (!process_cmd_token(new_cmd, &head, &info))
			return (ft_free_cmd(new_cmd), ft_free_cmd(cmd), NULL);
		add_cmd_to_list(&cmd, &tail, new_cmd);
		if (!handle_pipe(&head, error_code, cmd))
			return (NULL);
	}
	return (cmd);
}