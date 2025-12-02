/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:27:03 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 19:27:04 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	*get_img_ptr(t_map *map, t_tex_id type)
{
	if (type == TEX_WALL)
		return (map->textures.wall.img);
	else if (type == TEX_FLOOR)
		return (map->textures.floor.img);
	else if (type == TEX_PLAYER)
		return (map->textures.player.img);
	else if (type == TEX_COLL)
		return (map->textures.collectible.img);
	else if (type == TEX_EXIT)
		return (map->textures.exit.img);
	else if (type == TEX_P_EXIT)
		return (map->textures.p_e_floor.img);
	return (NULL);
}

void	render_sprite(t_map *m, t_pos pos, t_tex_id type)
{
	void	*img_ptr;

	img_ptr = get_img_ptr(m, type);
	if (!img_ptr)
		return ;
	mlx_put_image_to_window(m->mlx, m->win, img_ptr, pos.x * TS, pos.y * TS);
}

void	render_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			render_sprite(map, (t_pos){j, i}, TEX_FLOOR);
			if (map->map[i][j] == '1')
				render_sprite(map, (t_pos){j, i}, TEX_WALL);
			else if (map->map[i][j] == 'C')
				render_sprite(map, (t_pos){j, i}, TEX_COLL);
			else if (map->map[i][j] == 'P')
				render_sprite(map, (t_pos){j, i}, TEX_PLAYER);
			else if (map->map[i][j] == 'E')
				render_sprite(map, (t_pos){j, i}, TEX_EXIT);
			j++;
		}
		i++;
	}
}
