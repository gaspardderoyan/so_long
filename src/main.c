#include "../libft/inc/libft.h"
#include <stddef.h>
#include <sys/types.h>

enum Cell {
	EMPTY = 1,
	WALL,
	COIN,
	EXIT,
	START
};

typedef struct s_position {
	int	x;
	int	y;
} t_position;

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

/**
 * @brief calculate the len of the initial segment of 's' which contains only
 * chars from 'accept'
 */
size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	len;

	len = 0;
	while (s && *s)
	{
		if (ft_strchr(accept, *s))
			len++;
		s++;
	}
	return (len);
}

void	check_line(char *line, u_int8_t *found)
{
	while (line && *line)
	{
		if ((*found & 1 && *line == 'E') || (*found & 2 && *line == 'P'))
			*found |= 4;
		else if (*line == 'E')
			*found |= 1;
		else if (*line == 'P')
			*found |= 2;
		line++;
	}
}

/**
 * @brief check if the map is valid
 *
 * @return true if it is, false if not valid
 *
 * compare strspn with len - 1 to account for the \n at the end
 */
bool	check_map(t_list *char_map, size_t lines)
{
	size_t		first_len;
	size_t		i;
	u_int8_t	found;
	
	first_len = strlen_safe(char_map->content);
	if (ft_strspn(char_map->content, "1") != first_len - 1
		|| ft_strspn(ft_lstlast(char_map)->content, "1") != first_len - 1)
			   return (ft_printf("First or last line not walls!\n"), false);
	i = 0;
	found = 0;
	while (char_map)
	{
		if (strlen_safe(char_map->content) != first_len)
			return (ft_printf("Not a rectangle!\n"), false);
		if (i != 0 && i != lines - 1 && (((char *)(char_map->content))[0] != '1'
			|| ((char *)(char_map->content))[first_len - 2] != '1'))
			   return (ft_printf("First or last char not wall!\n"), false);
		check_line(char_map->content, &found);
		char_map = char_map->next;
		i++;
	}
	if (found != 3)
		return (ft_printf("Invalid count of exit/start cells\n", found), false);
	return (true);
}

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


#include <fcntl.h>
int main(int ac, char **av)
{
	int			fd;
	size_t		lines;
	char		*res;
	t_list		*char_map;
	u_int8_t	**map;
	t_position	*start;

	if (ac != 2)
		return(ft_printf("Wrong number of args! Please provide 1 .ber map\n"), 0);
	if (ft_strnstr(av[1], ".ber", strlen_safe(av[1])) == NULL)
		return(ft_printf("Map must have the .ber extension!"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd <= -1)
		return (ft_printf("Error opening file!\n"), 1);
	lines = 0;
	res = NULL;
	char_map = NULL;
	while (lines == 0 || res)
	{
		res = get_next_line(fd);
		if (!res)
			break ;
		ft_printf("Line %d: %s", lines, res);
		ft_lstadd_back(&char_map, ft_lstnew(res));
		lines++;
	}
	map = NULL;
	start = malloc(sizeof(t_position));
	if (!check_map(char_map, lines))
		ft_printf("Map not OK\n");
	else
	{
		ft_printf("Map is valid :)\n");
		map = convert_map(char_map, lines, start);
		if (bfs(map, start))
			printf("BFS OK!\n");
		else
			printf("BFS KO :(\n");
		print_map(map);
	}
	return (ft_lstfree(char_map), close(fd), 0);
}
