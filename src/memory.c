#include "../inc/so_long.h"
#include "../inc/error.h"

/**
 * @brief Frees the memory allocated for the map
 *
 * @param map 2D array representing the map
 * @param lines Number of lines in the map
 */
void	free_map(u_int8_t **map, size_t lines)
{
	size_t	i;
	
	if (!map)
		return ;
		
	i = 0;
	while (i < lines)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

/**
 * @brief Frees the memory allocated for the master structure
 *
 * @param master Pointer to the master structure
 */
void	free_master(t_master *master)
{
	if (!master)
		return ;
		
	if (master->start)
		free(master->start);
		
	if (master->char_map)
		ft_lstfree(master->char_map);
		
	if (master->map)
		free_map(master->map, master->lines);
		
	free(master);
} 