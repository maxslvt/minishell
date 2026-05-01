#include "minishell.h"

t_var	*new_var(char *envp_line)
{
	t_var	*new;
	char	*equal_pos;

	equal_pos = ft_strchr(envp_line, '=');
	if (!equal_pos)
		return (NULL);
	new = ft_calloc(1, sizeof(t_var));
	if (!new)
		return (NULL);
	new->name = ft_strndup(envp_line, equal_pos - envp_line);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(equal_pos + 1);
	if (!new->value)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_var	*create_uid_node(void)
{
	t_var	*new;
	char	*uid_str;

	uid_str = ft_itoa(getuid());
	if (!uid_str)
		return (NULL);
	new = ft_calloc(1, sizeof(t_var));
	if (!new)
		return (free(uid_str), NULL);
	new->name = ft_strdup("UID");
	new->value = uid_str;
	if (!new->name)
		return (free(uid_str), free(new), NULL);
	return (new);
}

static void	add_uid_to_env(t_var *env)
{
	t_var	*curr;
	t_var	*new;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->name, "UID") == 0)
			return ;
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	new = create_uid_node();
	if (new && curr)
	{
		curr->next = new;
		new->prev = curr;
	}
}

t_var	*create_env(char **envp)
{
	t_var	*head;
	t_var	*current;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	head = new_var(envp[0]);
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (envp[i])
	{
		current->next = new_var(envp[i]);
		if (!current->next)
		{
			ft_free_env(head);
			return (NULL);
		}
		current->next->prev = current;
		current = current->next;
		i++;
	}
	add_uid_to_env(head);
	return (head);
}