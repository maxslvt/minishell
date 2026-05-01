#include "minishell.h"

static void	free_var_node(t_var *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

static void	find_and_remove_var(char *name, t_var **env_list)
{
	t_var	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->prev == NULL)
				*env_list = current->next;
			else
				current->prev->next = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free_var_node(current);
			return ;
		}
		current = current->next;
	}
}

int	ft_unset(t_cmd *cmd, t_var **env_list)
{
	int	i;

	if (!cmd->cmd[1])
		return (0);
	i = 1;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][0] == '-' && cmd->cmd[i][1])
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(cmd->cmd[i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			return (2);
		}
		find_and_remove_var(cmd->cmd[i], env_list);
		i++;
	}
	return (0);
}