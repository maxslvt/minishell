#include "minishell.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static int	should_skip(char *src, int *i, char *quote)
{
	if (src[*i] == '$' && !*quote && src[*i + 1] == '\'')
	{
		*quote = '\'';
		(*i)++;
		return (1);
	}
	if ((src[*i] == '\'' || src[*i] == '"') && !*quote)
	{
		*quote = src[*i];
		return (1);
	}
	if (src[*i] == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	remove_quotes_process(char *src, char *dst)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (!should_skip(src, &i, &quote))
		{
			if (dst)
				dst[j++] = src[i];
			else
				j++;
		}
		i++;
	}
	if (dst)
		dst[j] = '\0';
	return (j);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*res;

	if (!str)
		return (NULL);
	len = remove_quotes_process(str, NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	remove_quotes_process(str, res);
	return (res);
}