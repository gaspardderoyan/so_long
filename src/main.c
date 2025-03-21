#include "../libft/inc/libft.h"
#include "../inc/so_long.h"
#include "../inc/error.h"

/**
 * @brief Prints the map to standard output
 *
 * @param map 2D array representing the map
 * @param free_map Flag indicating whether to free the map memory
 */
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

/**
 * @brief Main function of the program
 *
 * @param ac Argument count
 * @param av Argument vector
 * @return int Exit status
 */
int main(int ac, char **av)
{
	int			fd;
	t_master	*master;
	t_error		err;

	if (ac != 2)
	{
		handle_error(ERR_INVALID_ARGS, "Wrong number of args! Please provide 1 .ber map");
		return (1);
	}
	if (ft_strnstr(av[1], ".ber", strlen_safe(av[1])) == NULL)
	{
		handle_error(ERR_INVALID_ARGS, "Map must have the .ber extension!");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd <= -1)
	{
		handle_error(ERR_FILE_OPEN, "Error opening file!");
		return (1);
	}

	master = init_master();
	if (!master)
	{
		handle_error(ERR_MALLOC_FAIL, "Master struct initialisation failed!");
		close(fd);
		return (1);
	}
	
	err = process_map(fd, master);
	if (err != ERR_SUCCESS)
	{
		free_master(master);
		close(fd);
		return (1);
	}

	master->map = convert_map(master->char_map, master->lines, master->start);
	if (!master->map)
	{
		handle_error(ERR_MALLOC_FAIL, "Map conversion failed!");
		free_master(master);
		close(fd);
		return (1);
	}
	
	if (bfs(master->map, master->start) == ERR_SUCCESS)
		ft_printf("BFS OK!\n");
	else
		ft_printf("BFS KO :(\n");
	
	print_map(master->map, false);
	ft_lstfree(master->char_map);
	close(fd);
	return (0);
}
