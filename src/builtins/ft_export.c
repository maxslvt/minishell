#include "minishell.h"

static void	add_var_to_env(t_var **env_list, char *name, char *value)
{
	t_var	*new_var;
	t_var	*current;

	new_var = malloc(sizeof(t_var));
	if (!new_var)
		return (free(name), free(value));
	new_var->name = name;
	new_var->value = value;
	new_var->next = NULL;
	if (!*env_list)
	{
		*env_list = new_var;
		new_var->prev = NULL;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_var;
	new_var->prev = current;
}

static int	update_or_add_var(t_var **env, char *name, char *value)
{
	t_var	*existing;

	existing = find_var(*env, name);
	if (existing)
	{
		free(name);
		if (value)
		{
			free(existing->value);
			existing->value = value;
		}
		return (0);
	}
	add_var_to_env(env, name, value);
	return (0);
}

static int	handle_export_arg(char *arg, t_var **env_list)
{
	char	*name;
	char	*value;

	if (parse_export_arg(arg, &name, &value))
		return (1);
	if (valid_name(name))
		return (err_export(arg), free(name), free(value), 1);
	return (update_or_add_var(env_list, name, value));
}

static int	print_export(t_var *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_var **env_list)
{
	int	i;
	int	error;
	int	end_opt;
	int	ret;

	if (!cmd->cmd[1])
		return (print_export(*env_list));
	i = 1;
	error = 0;
	end_opt = 0;
	while (cmd->cmd[i])
	{
		ret = check_option(cmd->cmd[i], &end_opt);
		if (ret == 2)
			return (2);
		if (ret == 0 && handle_export_arg(cmd->cmd[i], env_list))
			error = 1;
		i++;
	}
	return (error);
}