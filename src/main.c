#include "../libft/inc/libft.h"
#include "../inc/so_long.h"

u_int8_t *convert_line(char *line, size_t len, size_t i, t_position *start)
{
	u_int8_t	*row;	
	size_t		j;

	row = ft_calloc(len, sizeof(u_int8_t));
	if (!row)
		return (ft_printf("Malloc for single row failed!\n"), NULL);
	j = 0;
	while (line && line[j])
	{
		if (line[j] == '\n')
			row[j] = 0;
		else if (line[j] == '0')
			row[j] = EMPTY;
		else if (line[j] == '1')
			row[j] = WALL;
		else if (line[j] == 'C')
			row[j] = COIN;
		else if (line[j] == 'E')
			row[j] = EXIT;
		else if (line[j] == 'P')
		{
			row[j] = START;
			start->x = i;
			start->y = j;
		}
		j++;
	}
	return (row);
}

u_int8_t **convert_map(t_list *char_map, size_t lines, t_position *start)
{
	u_int8_t	**map;
	size_t		i;
	size_t		len;


	map = ft_calloc(lines + 1, sizeof(u_int8_t*));
	if (!map)
		return (ft_printf("Malloc for whole map failed!"), NULL);
	len = strlen_safe(char_map->content);
	i = 0;
	while (i < lines && char_map)
	{
		map[i] = convert_line(char_map->content, len, i, start);
		char_map = char_map->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	print_map(u_int8_t **map, bool free_map)
{
	int	i;
	int	j;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_printf("%d", map[i][j]);
			j++;
		}
		ft_printf("\n");
		if (free_map)
			free(map[i]);
		i++;
	}
	if (free_map)
		free(map);
}



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
	void	*content;

	if (!*head)
		return (NULL);
	popped_node = *head;
	*head = (*head)->next;
	content = popped_node->content;
	free(popped_node);
	return (content);
}

bool	bfs(u_int8_t **map, t_position *start)
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
				return (free(current_position), true);
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
	return (false);
}


int main(int ac, char **av)
{
	int			fd;
	t_master	*master;

	if (ac != 2)
		return(ft_printf("Wrong number of args! Please provide 1 .ber map\n"), 0);
	if (ft_strnstr(av[1], ".ber", strlen_safe(av[1])) == NULL)
		return(ft_printf("Map must have the .ber extension!"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd <= -1)
		return (ft_printf("Error opening file!\n"), 1);

	master = init_master();
	process_map(fd, master);

	master->map = convert_map(master->char_map, master->lines, master->start);
	if (bfs(master->map, master->start))
		printf("BFS OK!\n");
	else
		printf("BFS KO :(\n");
	print_map(master->map, false);
	return (ft_lstfree(master->char_map), close(fd), 0);
}
