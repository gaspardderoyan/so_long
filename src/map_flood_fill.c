#include "../includes/so_long.h"

void	copy_map(t_map *map)
{
	int	i;

	i = 0;
	map->map_copy = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_copy)
		exit_error("You've ran out of memory!", map);
	while (map->map[i])
	{
		map->map_copy[i] = ft_strdup(map->map[i]);
		if (!map->map_copy[i])
			exit_error("You've ran out of memory!", map);
		i++;
	}
	map->map_copy[i] = NULL;
}

void	flood_fill(t_map *map, t_pos pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= (int)map->width
		|| pos.y >= (int)map->height || map->map_copy[pos.y][pos.x] == '1'
		|| map->map_copy[pos.y][pos.x] == 'X')
		return ;
	if (map->map_copy[pos.y][pos.x] == 'E')
		map->exit_total++;
	else if (map->map_copy[pos.y][pos.x] == 'C')
		map->coin_total++;
	map->map_copy[pos.y][pos.x] = 'X';
	flood_fill(map, (t_pos){pos.x + 1, pos.y});
	flood_fill(map, (t_pos){pos.x, pos.y + 1});
	flood_fill(map, (t_pos){pos.x - 1, pos.y});
	flood_fill(map, (t_pos){pos.x, pos.y - 1});
}

void	flood_fill_check(t_map *map)
{
	if (map->coin_count != map->coin_total)
		exit_error("Not all coins are reachable!", map);
	if (map->exit_count != map->exit_total)
		exit_error("The exit isn't reachable!", map);
}
