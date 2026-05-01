#include "minishell.h"

static int	init_heredoc(t_redirect *redir, t_token *cur)
{
	char	*clean_n;

	redir->is_heredoc = 1;
	if (cur->next)
	{
		if (has_quotes(cur->next->value))
			redir->expand_heredoc = 0;
		else
			redir->expand_heredoc = 1;
		clean_n = remove_quotes(cur->next->value);
		if (!clean_n)
			return (0);
		redir->eof = clean_n;
		redir->files = NULL;
	}
	return (1);
}

static int	init_file_redir(t_redirect *redir, t_token *cur, t_var *env,
	int status)
{
	char	*expanded;
	char	*clean_n;

	if (cur->next)
	{
		expanded = ft_expand(cur->next->value, env, status);
		if (!expanded)
			return (0);
		if (expanded[0] == '\0' || is_ambiguous(expanded))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cur->next->value, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			free(expanded);
			return (0);
		}
		clean_n = remove_quotes(expanded);
		free(expanded);
		if (!clean_n)
			return (0);
		redir->files = clean_n;
	}
	else
		redir->files = NULL;
	return (1);
}

t_redirect	*create_redirect(t_token *cur, t_var *env, int status)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = cur->type;
	redir->next = NULL;
	redir->is_heredoc = 0;
	redir->expand_heredoc = 1;
	redir->eof = NULL;
	if (cur->type == HEREDOC)
		init_heredoc(redir, cur);
	else if (!init_file_redir(redir, cur, env, status))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

