#include "minishell.h"

int	valid_name(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (-1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

void	err_export(char *name)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_varsize(t_var *env)
{
	int		i;
	t_var	*tmp;

	if (!env)
		return (0);
	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	is_valid_env_var(char *str)
{
	int	i;

	if (!str || str[0] != '$')
		return (1);
	i = 1;
	if (str[i] == '\0') 
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
