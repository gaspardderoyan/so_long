/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:26:58 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 19:27:00 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_map_loop(t_map *map)
{
	size_t	i;
	size_t	len;

	i = 0;
	map->width = ft_strlen_safe(map->map[0]);
	while (map->map[i])
	{
		len = ft_strlen_safe(map->map[i]);
		if (len == 0)
			exit_error("Line too short!.", map);
		if (map->width != len)
			exit_error("Map with unequal line length.", map);
		if (ft_strspn(map->map[i], "01CEP") != map->width)
			exit_error("Map with wrong tile.", map);
		if (map->map[i][0] != '1' || map->map[i][len - 1] != '1')
			exit_error("First or last column not only obstacles", map);
		map->exit_count += get_chars_count(map->map[i], "E");
		map->coin_count += get_chars_count(map->map[i], "C");
		map->player_count += get_chars_count(map->map[i], "P");
		i++;
	}
}

static t_pos	find_char_in_map(t_map *map, char c)
{
	int		i;
	char	*target;

	i = 0;
	target = NULL;
	while (map->map[i])
	{
		target = ft_strchr(map->map[i], c);
		if (target)
			return ((t_pos){target - map->map[i], i});
		i++;
	}
	return ((t_pos){0, 0});
}

void	check_map_final(t_map *map)
{
	if (ft_strspn(map->map[0], "1") != map->width
		|| ft_strspn(map->map[map->height - 1], "1") != map->width)
		exit_error("First or last row not only obstacles.", map);
	if (map->exit_count != 1 || map->player_count != 1
		|| map->coin_count < 1)
		exit_error("Wrong count of 'exit','player' or 'coin' tiles.", map);
	map->position = find_char_in_map(map, 'P');
	map->exit = find_char_in_map(map, 'E');
}
