#include "../libft/inc/libft.h"
#include "../inc/so_long.h"
#include "../inc/error.h"

/**
 * @brief Checks if a position is already in the queue
 *
 * @param lst The list to check
 * @param pos The position to look for
 * @return true if position is in queue, false otherwise
 */
static bool	is_pos_in_queue(t_list *lst, t_position *pos)
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

/**
 * @brief Gets the surrounding cells of a position
 *
 * @param pos The central position
 * @param surrounding_cells Array to store the surrounding positions
 */
static void	get_surrounding_cells(t_position pos, t_position *surrounding_cells)
{
	surrounding_cells[0] = (t_position){ .x = pos.x + 1, .y = pos.y };
	surrounding_cells[1] = (t_position){ .x = pos.x, .y = pos.y + 1};
	surrounding_cells[2] = (t_position){ .x = pos.x - 1, .y = pos.y};
	surrounding_cells[3] = (t_position){ .x = pos.x, .y = pos.y - 1};
}

/**
 * @brief performs a breadth-first search on the map
 *
 * @param map 2D array representing the map
 * @param start Starting position
 * @return t_error ERR_SUCCESS if exit is reachable, ERR_MAP_INVALID otherwise
 */
t_error	bfs(u_int8_t **map, t_position *start)
{
	t_list		*queue = NULL;
	t_list		*seen = NULL;
	t_position	*current_position;
	t_position	adj_cells[4];
	size_t		i;

	ft_lstadd_back(&queue, ft_lstnew(start));
	ft_lstadd_back(&seen, ft_lstnew(start));

	while (ft_lstsize(queue) != 0)
	{
		current_position = (t_position*)ft_lstpop(&queue);
		if (!current_position)
			break ;

		get_surrounding_cells(*current_position, (t_position*)&adj_cells);
		i = 0;
		while (i < 4)
		{
			int current_value = map[adj_cells[i].x][adj_cells[i].y];
			if (current_value == EXIT)
				return (ERR_SUCCESS);
			else if (!is_pos_in_queue(seen, &adj_cells[i]) && current_value != WALL)
			{
				t_position *new = malloc(sizeof(t_position));
				*new = adj_cells[i];
				ft_lstadd_back(&queue, ft_lstnew(new));
				ft_lstadd_back(&seen, ft_lstnew(new));
			}
			i++;
		}
	}
	return (ERR_MAP_INVALID);
}
