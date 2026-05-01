#include "minishell.h"

int	process_redir(t_cmd *new_cmd, t_token **cur, t_parse_info *info)
{
	if (!check_redir_syntax((*cur)->next))
	{
		if (info->error_code)
			*info->error_code = 2;
		return (0);
	}
	if (!add_redirect(new_cmd, *cur, info->env, info->status))
	{
		if (info->error_code)
			*info->error_code = 1;
		return (0);
	}
	*cur = (*cur)->next;
	return (1);
}

void	append_redirect(t_cmd *cmd, t_redirect *redir)
{
	t_redirect	*tmp;

	if (!cmd->redirect)
		cmd->redirect = redir;
	else
	{
		tmp = cmd->redirect;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	add_redirect(t_cmd *new_cmd, t_token *cur, t_var *env, int status)
{
	t_redirect	*redir;

	redir = create_redirect(cur, env, status);
	if (!redir)
		return (0);
	append_redirect(new_cmd, redir);
	new_cmd->nb_redirect++;
	return (1);
}

int	check_redir_syntax(t_token *next)
{
	char	*error_token;

	if (!next)
		error_token = "newline";
	else if (next->type != WORD)
		error_token = next->value;
	else
		return (1);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}
