#include "minishell.h"

// Alloue et initialise une nouvelle structure t_cmd.
t_cmd	*cmd_new(char **argv, int *infile_fd, int outfile_fd)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = argv;
	new_cmd->nb_redirect = 0;
	new_cmd->redirect = NULL;
	new_cmd->infile = infile_fd;
	new_cmd->outfile = outfile_fd;
	new_cmd->code = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->nb_redirect = 0;
	new_cmd->redirect = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = -1;
	new_cmd->code = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_cmd_to_list(t_cmd **cmd, t_cmd **tmp, t_cmd *new_cmd)
{
	if (!*cmd)
		*cmd = new_cmd;
	else
		(*tmp)->next = new_cmd;
	*tmp = new_cmd;
}

static char	**realloc_args(char **cmd, char *value)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		new_arr[i] = cmd[i];
		i++;
	}
	new_arr[i] = ft_strdup(value);
	if (!new_arr[i])
	{
		free(new_arr);
		return (NULL);
	}
	new_arr[i + 1] = NULL;
	return (new_arr);
}

void	add_arg(t_cmd *new_cmd, char *value)
{
	char	**new_arr;

	if (!new_cmd || !value)
		return ;
	new_arr = realloc_args(new_cmd->cmd, value);
	if (!new_arr)
		return ;
	if (new_cmd->cmd)
		free(new_cmd->cmd);
	new_cmd->cmd = new_arr;
}