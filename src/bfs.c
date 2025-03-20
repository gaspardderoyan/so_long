#include "../libft/inc/libft.h"

typedef struct s_position {
	int	x;
	int	y;
} t_position;

enum Cell {
	EMPTY = 1,
	WALL,
	COIN,
	EXIT,
	START
};

bool	is_pos_in_queue(t_list *lst, t_position *pos)
{
	while (lst)
	{
		if (((t_position*)(lst->content))->x == pos->x 
			&& ((t_position*)(lst->content))->y == pos->y)
			return (true);
		lst = lst->next;
	}
	return (false);
}

void	get_surrounding_cells(t_position pos, t_position *surrounding_cells)
{
	surrounding_cells[0] = (t_position){ .x = pos.x + 1, .y = pos.y };
	surrounding_cells[1] = (t_position){ .x = pos.x, .y = pos.y + 1};
	surrounding_cells[2] = (t_position){ .x = pos.x - 1, .y = pos.y};
	surrounding_cells[3] = (t_position){ .x = pos.x, .y = pos.y - 1};
}

void	*ft_lstpop(t_list **head)
{
	t_list	*popped_node;

	popped_node = *head;
	popped_node->next = NULL;
	*head = (*head)->next;
	return (popped_node);
}

bool	bfs(int **map, t_position *start)
{
	t_list		*queue;
	t_list		*seen;
	t_position	*current_position;
	t_position	adj_cells[4];
	size_t		i;

	ft_lstadd_back(&queue, ft_lstnew(start));
	ft_lstadd_back(&seen, ft_lstnew(start));

	while (ft_lstsize(queue) != 0)
	{
		current_position = ft_lstpop(&queue);
		if (!current_position)
			break ;

		get_surrounding_cells(*current_position, (t_position*)&adj_cells);
		i = 0;
		while (i < 4)
		{
			int current_value = map[adj_cells[i].x][adj_cells[i].y];
			if (current_value == EXIT)
				return (true);
			else if (!is_pos_in_queue(seen, &adj_cells[i]) && current_value != WALL)
			{
				ft_lstadd_back(&queue, ft_lstnew(&adj_cells[i]));
				ft_lstadd_back(&seen, ft_lstnew(&adj_cells[i]));
			}
			i++;
		}
	}
	return (false);
}
