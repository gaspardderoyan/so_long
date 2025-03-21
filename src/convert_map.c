#include "../libft/inc/libft.h"
#include "../inc/so_long.h"
#include "../inc/error.h"

/**
 * @brief Converts a character line to a numeric row
 *
 * @param line The character line to convert
 * @param len The length of the line
 * @param i The row index
 * @param start Pointer to store the start position
 * @return u_int8_t* The converted numeric row
 */
static u_int8_t *convert_line(char *line, size_t len, size_t i, t_position *start)
{
	u_int8_t	*row;	
	size_t		j;

	row = ft_calloc(len, sizeof(u_int8_t));
	if (!row)
	{
		handle_error(ERR_MALLOC_FAIL, "Malloc for single row failed!");
		return (NULL);
	}
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

/**
 * @brief Converts the character map to a numeric map
 *
 * @param char_map List containing the character map
 * @param lines Number of lines in the map
 * @param start Pointer to store the start position
 * @return u_int8_t** The converted numeric map
 */
u_int8_t **convert_map(t_list *char_map, size_t lines, t_position *start)
{
	u_int8_t	**map;
	size_t		i;
	size_t		len;


	map = ft_calloc(lines + 1, sizeof(u_int8_t*));
	if (!map)
	{
		handle_error(ERR_MALLOC_FAIL, "Malloc for whole map failed!");
		return (NULL);
	}
	len = strlen_safe(char_map->content);
	i = 0;
	while (i < lines && char_map)
	{
		map[i] = convert_line(char_map->content, len, i, start);
		if (!map[i])
		{
			free_map(map, i);
			return (NULL);
		}
		char_map = char_map->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}
