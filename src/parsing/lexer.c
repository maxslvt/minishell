#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	check_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
	{
		quote = str[i + 1];
		i += 2;
		while (str[i] && str[i] != quote)
			i++;
		if (str[i] == quote)
			return (i + 1);
		return (ft_putstr_fd("syntax error: unclosed quote\n", 2), -1);
	}
	if (str[i] == '"' || str[i] == '\'')
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
		if (str[i] == quote)
			return (i + 1);
		return (ft_putstr_fd("syntax error: unclosed quote\n", 2), -1);
	}
	return (0);
}

static int	copy_quoted(char *res, int *j, char *str, int *i)
{
	char	quote;

	if (str[*i] == '$' && (str[*i + 1] == '"' || str[*i + 1] == '\''))
	{
		res[(*j)++] = '$';
		(*i)++;
	}
	quote = str[*i];
	res[(*j)++] = quote;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		res[(*j)++] = str[(*i)++];
	if (!str[*i])
		return (0);
	res[(*j)++] = quote;
	(*i)++;
	return (1);
}

char	*extract_quoted(char *str, int len)
{
	char	*res;
	int		i;
	int		j;

	if (!str || len <= 0)
		return (NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if ((str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			|| str[i] == '"' || str[i] == '\'')
		{
			if (!copy_quoted(res, &j, str, &i))
				return (free(res), ft_putstr_fd("syntax error: \
				unclosed quote\n", 2), NULL);
		}
		else if (i < len && str[i] != '\0'
			&& !(str[i] == '"' || str[i] == '\''))
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}