#include "../includes/so_long.h"

void	init_struct(t_map *map)
{
	map->coin_count = 0;
	map->coin_current = 0;
	map->exit_count = 0;
	map->player_count = 0;
	map->coin_total = 0;
	map->exit_total = 0;
	map->height = 0;
	map->width = 0;
	map->map = NULL;
	map->map_copy = NULL;
	map->map_lst = NULL;
	map->moves = 0;
	map->mlx = NULL;
	map->win = NULL;
	map->textures.wall.img = NULL;
	map->textures.floor.img = NULL;
	map->textures.collectible.img = NULL;
	map->textures.player.img = NULL;
	map->textures.exit.img = NULL;
	map->textures.p_e_floor.img = NULL;
}

static t_mlx_data	load_texture(t_map *map, char *path)
{
	t_mlx_data	i;
	void		*p;	

	i.img = mlx_xpm_file_to_image(map->mlx, path, &i.width, &i.height);
	if (!i.img)
		exit_error("Texture could not be loaded. Check file path!", map);
	p = mlx_get_data_addr(i.img, &i.bits_per_px, &i.line_length, &i.endian);
	i.addr = p;
	return (i);
}

void	load_all_textures(t_map *map)
{
	map->textures.collectible = load_texture(map, "./textures/collectible.xpm");
	map->textures.floor = load_texture(map, "./textures/floor.xpm");
	map->textures.p_e_floor = load_texture(map, "./textures/p_e_floor.xpm");
	map->textures.exit = load_texture(map, "./textures/exit.xpm");
	map->textures.player = load_texture(map, "./textures/player.xpm");
	map->textures.wall = load_texture(map, "./textures/wall.xpm");
}
