#include "minishell.h"

int	check_pipe_syntax(t_token *cur, int *error_code)
{
	if (!cur || cur->type == PIPE)
	{
		if (error_code)
			*error_code = 2;
		return (0);
	}
	return (1);
}

int	pipe_error(t_cmd *cmd)
{
	ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
	return (ft_free_cmd_list(cmd), 2);
}

int	is_ambiguous(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (!quote && is_whitespace(str[i]))
			return (1);
		i++;
	}
	return (0);
}