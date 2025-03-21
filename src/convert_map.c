#include "../libft/inc/libft.h"
#include "../inc/so_long.h"

static u_int8_t *convert_line(char *line, size_t len, size_t i, t_position *start)
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
