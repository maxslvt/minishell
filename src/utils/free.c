#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_cmd(t_cmd *c)
{
	t_redirect	*redir;
	t_redirect	*next_redir;

	if (!c)
		return ;
	if (c->cmd)
		ft_free_tab(c->cmd);
	redir = c->redirect;
	while (redir)
	{
		next_redir = redir->next;
		if (redir->files)
			free(redir->files);
		if (redir->eof)
			free(redir->eof);
		free(redir);
		redir = next_redir;
	}
	if (c->infile)
		free(c->infile);
	free(c);
}

void	ft_free_cmd_list(t_cmd *list)
{
	t_cmd	*current;
	t_cmd	*next_node;

	current = list;
	while (current)
	{
		next_node = current->next;
		ft_free_cmd(current);
		current = next_node;
	}
}

void	ft_free_env(t_var *env)
{
	t_var	*current;
	t_var	*next_node;

	current = env;
	while (current)
	{
		next_node = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next_node;
	}
}

void	ft_free_exit(t_cmd *cmd, t_var **env, int last_status)
{
	int	fd;

	if (env)
		ft_free_env(*env);
	if (cmd)
		ft_free_cmd_list(cmd);
	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	exit(last_status);
}