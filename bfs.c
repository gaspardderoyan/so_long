#include "../libft/inc/libft.h"

typedef struct s_position {
	int	x;
	int	y;
} t_position;

bool	bfs(int **map, t_position *start)
{
	t_list		*queue;
	t_list		*seen;
	t_position	*current_position;
	t_position	*adj_cells[5];

	ft_lstadd_back(&queue, ft_lstnew(start));
	ft_lstadd_back(&seen, ft_lstnew(start));

	while (ft_lstsize(queue) != 0)
	{
		current_position = lst_pop(queue, 0);
		if (!current_position)
			break ;

		adj_cells = get_surrounding_cells(current_position);
		i = 0;
		while (surrounding_cells[i] != NULL)
		{
			int current_value = map[adj_cells[i].x][adj_cells[i].y];
			if (current_value == EXIT)
				return (true);
			else if (!lst_contains(adj_cells[i]) && current_value != WALL)
				ft_lstadd_back(&queue, ft_lstnew(adj_cells[i]));
				ft_lstadd_back(&seen, ft_lstnew(adj_cells[i]));
			i++;
		}
	}
	return (false);
}
