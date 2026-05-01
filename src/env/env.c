#include "minishell.h"

static size_t	get_env_size(t_var *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

static char	*create_env_str(t_var *var)
{
	char	*str;
	size_t	len;

	if (!var->name)
		return (ft_strdup(""));
	if (!var->value)
		return (ft_strjoin(var->name, "="));
	len = ft_strlen(var->name) + ft_strlen(var->value) + 2;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, var->name, len);
	ft_strlcat(str, "=", len);
	ft_strlcat(str, var->value, len);
	return (str);
}

char	**convert_env_list(t_var *list)
{
	char	**env_array;
	size_t	size;
	int		i;

	size = get_env_size(list);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (list)
	{
		env_array[i] = create_env_str(list);
		if (!env_array[i])
		{
			ft_free_tab(env_array);
			return (NULL);
		}
		list = list->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*get_env_value(char *name, t_var *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}