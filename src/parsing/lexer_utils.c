#include "minishell.h"

int	get_token_len(char *s)
{
	int		i;
	int		qlen;

	i = 0;
	if (s[0] == '|' || s[0] == '<' || s[0] == '>')
	{
		if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>')
			|| (s[0] == '<' && s[1] == '>'))
			return (2);
		return (1);
	}
	while (s[i] && !is_whitespace(s[i]) && !is_special(s[i]))
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			qlen = check_quote(&s[i]);
			if (qlen < 0)
				return (-1);
			i += qlen;
		}
		else
			i++;
	}
	return (i);
}

char	*ft_chrdup(char c)
{
	char	*s;

	s = malloc(2);
	if (!s)
		return (NULL);
	s[0] = c;
	s[1] = 0;
	return (s);
}