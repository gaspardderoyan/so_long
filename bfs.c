#include "../libft/inc/libft.h"

typedef struct s_position {
	int	x;
	int	y;
} t_position;

int	bfs(int **map, t_position *start)
{
	t_list		*queue;
	t_list		*seen;
	t_position	*current;
	t_position			surrounding_cells[5];
	int			i;

	lst_add_back(queue, start);
	lst_add_back(seen, start);

	while (lst_size(queue) != 0)
	{
		current = lst_pop(queue, 0);
		if (!current)
			break ;

		surrounding_cells = get_surrounding_cells(current);
		i = 0;
		while (surrounding_cells[i])
		{
			if map[][]
		}
	}
}
