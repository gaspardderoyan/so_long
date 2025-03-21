#include "../libft/inc/libft.h"
#include "../inc/so_long.h"
#include "../inc/error.h"

/**
 * @brief Initializes the master structure
 *
 * @return t_master* Pointer to the initialized master structure
 */
t_master	*init_master(void)
{
	t_master	*master;
	
	master = ft_calloc(1, sizeof(t_master));
	if (!master)
		return (NULL);
	master->start = ft_calloc(1, sizeof(t_position));
	if (!master->start)
		return (free(master), NULL);
	master->lines = 0;
	master->len = 0;
	master->map = NULL;
	master->char_map = NULL;
	return (master);
}

/**
 * @brief Checks a line for exit and player positions
 *
 * @param line The line to check
 * @param found Pointer to a flag that tracks found entities
 */
static void	check_line(char *line, u_int8_t *found)
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
 * @brief Checks if the map is valid
 *
 * @param char_map List containing the map lines
 * @param lines Number of lines in the map
 * @return t_error ERR_SUCCESS if valid, specific error code otherwise
 */
static t_error	check_map(t_list *char_map, size_t lines)
{
	size_t		first_len;
	size_t		i;
	u_int8_t	found;
	
	first_len = strlen_safe(char_map->content);
	if (ft_strspn(char_map->content, "1") != first_len - 1
		|| ft_strspn(ft_lstlast(char_map)->content, "1") != first_len - 1)
	{
		handle_error(ERR_MAP_WALLS, "First or last line not walls!");
		return (ERR_MAP_WALLS);
	}
	i = 0;
	found = 0;
	while (char_map)
	{
		if (strlen_safe(char_map->content) != first_len)
		{
			handle_error(ERR_MAP_RECTANGLE, "Not a rectangle!");
			return (ERR_MAP_RECTANGLE);
		}
		if (i != 0 && i != lines - 1 && (((char *)(char_map->content))[0] != '1'
			|| ((char *)(char_map->content))[first_len - 2] != '1'))
		{
			handle_error(ERR_MAP_WALLS, "First or last char not wall!");
			return (ERR_MAP_WALLS);
		}
		check_line(char_map->content, &found);
		char_map = char_map->next;
		i++;
	}
	if (found != 3)
	{
		handle_error(ERR_MAP_ENTITIES, "Invalid count of exit/start cells");
		return (ERR_MAP_ENTITIES);
	}
	return (ERR_SUCCESS);
}

/**
 * @brief Processes and validates a map file
 *
 * @param fd File descriptor of the open map file
 * @param master Master structure to store the map data
 * @return t_error ERR_SUCCESS on success, specific error code on failure
 */
t_error	process_map(int	fd, t_master *master)
{
	char	*res;
	t_error err;

	res = NULL;
	if (!master)
	{
		handle_error(ERR_MALLOC_FAIL, "Master struct initialisation failed!");
		return (ERR_MALLOC_FAIL);
	}
	while (master->lines == 0 || res)
	{
		res = get_next_line(fd);
		if (!res)
			break ;
		ft_lstadd_back(&master->char_map, ft_lstnew(res));
		master->lines++;
	}
	err = check_map(master->char_map, master->lines);
	if (err != ERR_SUCCESS)
		return (err);
	ft_printf("First map check OK\n");
	return (ERR_SUCCESS);
}
