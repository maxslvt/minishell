#include "minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token	*elem;

	if (!value || type < 0)
		return (NULL);
	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

bool	add_token(char *value, int type, t_tok_list *list)
{
	t_token	*token;

	token = create_token(value, type);
	if (!token)
		return (false);
	if (list->head == NULL)
	{
		list->head = token;
		list->tail = token;
	}
	else
	{
		list->tail->next = token;
		list->tail = token;
	}
	return (true);
}

int	assign_type(char *str)
{
	if (!str || !*str)
		return (WORD);
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == '<' && str[1] == '>')
		return (REDIR_RDWR);
	if (str[0] == '>' && str[1] == '>')
		return (REDIR_APPEND);
	if (str[0] == '>')
		return (REDIR_OUT);
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	if (str[0] == '<')
		return (REDIR_IN);
	return (WORD);
}

static bool	process_token(char **ptr, t_tok_list *list)
{
	int		len;
	char	*sub;

	len = get_token_len(*ptr);
	if (len <= 0)
		return (false);
	sub = extract_quoted(*ptr, len);
	if (!sub || !add_token(sub, assign_type(sub), list))
		return (free(sub), false);
	*ptr += len;
	return (true);
}

t_token	*tokenize_line(char *line)
{
	char		*ptr;
	t_tok_list	list;

	ptr = line;
	list.head = NULL;
	list.tail = NULL;
	while (*ptr)
	{
		while (*ptr && is_whitespace(*ptr))
			ptr++;
		if (!*ptr)
			break ;
		if (!process_token(&ptr, &list))
		{
			free_and_null(&list);
			return (NULL);
		}
	}
	return (list.head);
}