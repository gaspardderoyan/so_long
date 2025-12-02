/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:26:41 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 19:26:42 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	move_player(t_map *map, t_pos new_pos)
{
	t_pos	last;

	if (map->map[new_pos.y][new_pos.x] == '1')
		return ;
	ft_printf("Current movement count: %d\n", ++(map->moves));
	last = (t_pos){map->position.x, map->position.y};
	if (new_pos.x == map->exit.x && new_pos.y == map->exit.y
		&& map->coin_current == map->coin_total)
		close_game(map);
	if (map->map[new_pos.y][new_pos.x] == 'C')
		map->coin_current++;
	if (last.y == map->exit.y && last.x == map->exit.x)
		render_sprite(map, last, TEX_EXIT);
	else
		render_sprite(map, last, TEX_FLOOR);
	if (last.y == map->exit.y && last.x == map->exit.x)
		map->map[last.y][last.x] = 'E';
	else
		map->map[last.y][last.x] = '0';
	map->position = new_pos;
	if (new_pos.x == map->exit.x && new_pos.y == map->exit.y)
		render_sprite(map, new_pos, TEX_P_EXIT);
	else
		render_sprite(map, new_pos, TEX_PLAYER);
}

int	key_press_handler(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
		close_game(map);
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(map, (t_pos){map->position.x, map->position.y - 1});
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(map, (t_pos){map->position.x, map->position.y + 1});
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(map, (t_pos){map->position.x - 1, map->position.y});
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(map, (t_pos){map->position.x + 1, map->position.y});
	return (0);
}
