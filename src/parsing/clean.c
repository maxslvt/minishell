#include "minishell.h"

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_and_null(t_tok_list *list)
{
	free_token_list(list->head);
	list->head = NULL;
	list->tail = NULL;
}