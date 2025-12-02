#include "../includes/so_long.h"

static void	free_map_array(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	destroy_images(t_map *map)
{
	if (map->textures.wall.img)
		mlx_destroy_image(map->mlx, map->textures.wall.img);
	if (map->textures.floor.img)
		mlx_destroy_image(map->mlx, map->textures.floor.img);
	if (map->textures.collectible.img)
		mlx_destroy_image(map->mlx, map->textures.collectible.img);
	if (map->textures.player.img)
		mlx_destroy_image(map->mlx, map->textures.player.img);
	if (map->textures.exit.img)
		mlx_destroy_image(map->mlx, map->textures.exit.img);
	if (map->textures.p_e_floor.img)
		mlx_destroy_image(map->mlx, map->textures.p_e_floor.img);
}

int	close_game(t_map *map)
{
	if (!map)
		exit(0);
	destroy_images(map);
	if (map->win)
		mlx_destroy_window(map->mlx, map->win);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	if (map->map)
		free_map_array(map->map);
	if (map->map_copy)
		free_map_array(map->map_copy);
	if (map->map_lst)
		ft_lstclear(&map->map_lst, free);
	exit(0);
	return (0);
}

void	exit_error(char *msg, t_map *map)
{
	ft_printf("Error: %s\n", msg);
	close_game(map);
}
