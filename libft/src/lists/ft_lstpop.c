#include "../../inc/libft.h"

void	*ft_lstpop(t_list **head)
{
	t_list	*popped_node;
	void	*content;

	if (!*head)
		return (NULL);
	popped_node = *head;
	*head = (*head)->next;
	content = popped_node->content;
	free(popped_node);
	return (content);
}
