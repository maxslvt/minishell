#include "minishell.h"

t_var	*find_var(t_var *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	parse_export_arg(char *arg, char **name, char **value)
{
	char	*equal_pos;

	if (!arg)
		return (1);
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		*name = ft_strdup(arg);
	else
		*name = ft_strndup(arg, equal_pos - arg);
	if (!*name)
		return (1);
	*value = NULL;
	if (equal_pos)
	{
		*value = ft_strdup(equal_pos + 1);
		if (!*value)
			return (free(*name), 1);
	}
	return (0);
}

int	check_option(char *arg, int *end_opt)
{
	if (!*end_opt && arg[0] == '-' && arg[1] != '\0')
	{
		if (arg[1] == '-' && arg[2] == '\0')
		{
			*end_opt = 1;
			return (1);
		}
		ft_putstr_fd("minishell: export: ", 2);
		write(2, arg, 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	return (0);
}