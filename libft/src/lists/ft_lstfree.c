#include "../../inc/libft.h"

void	ft_lstfree(t_list *lst)
{
	t_list *temp;

	temp = NULL;
	while(lst)
	{
		temp = lst;	
		lst = lst->next;
		free(temp->content);
		free(temp);
	}
}
