/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:01:45 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 16:36:22 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

size_t	ft_strlen_safe(char *str)
{
	size_t	len;	

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	int		i;

	i = 0;
	if (!s || !accept)
		return (0);
	while (s[i])
	{
		if (ft_strchr(accept, s[i]) == NULL)
			break ;
		i++;
	}
	return (i);
}

const char	*ft_strpbrk(const char *s, const char *accept)
{
	int		i;

	i = 0;
	if (!s || !accept)
		return (NULL);
	while (s[i] && ft_strchr(accept, s[i]) == NULL)
		i++;
	if (!s[i])
		return (NULL);
	return (&s[i]);
}

/**
 * @brief Counts the total occurrences of specific characters in a string.
 *
 * Scans the input string `str` and calculates how many times any character
 * contained in the delimiter string `chars` appears.
 *
 * @param str The string to be scanned (Haystack).
 * @param chars A string containing the characters to count (Needles).
 * @return size_t The total count of matching characters found.
 * Returns 0 if either input is NULL.
 */
size_t	get_chars_count(const char *str, char *chars)
{
	size_t	count;

	count = 0;
	if (!str || !chars)	
		return (0);
	while (1)
	{
		str = ft_strpbrk(str, chars);
		if (!str)
			break ;
		str++;
		count++;
	}
	return (count);
}

void	exit_error(char *msg)
{
	// TODO: add cleanup of memory
	ft_printf("Error: %s\n", msg);
	exit(1);
}
void	check_args(int ac, char **av)
{
	char *last_dot;

	if (ac != 2)
		exit_error("Please provide exactly 1 .ber map.\n");
	last_dot = ft_strrchr(av[1], '.');
	if (!last_dot || ft_strcmp(last_dot, ".ber"))
		exit_error("The map must be in .ber format.\n");
}

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
	map->exit_shown = false;
}

void	read_file_to_lst(char *filename, t_list **head)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Error opening file!");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
				  break ;
		ft_lstadd_back(head, ft_lstnew(line));
	}
}

void	lst_to_strs(t_map *map)
{
	int		i;
	t_list	*tmp;
	size_t	len;

	map->map = malloc(sizeof(char *) * (ft_lstsize(map->map_lst) + 1));
	if (!map->map)
		exit_error("Couldn't malloc for the **map.");
	i = 0;
	while (map->map_lst)
	{
		tmp = map->map_lst->next;
		map->map[i] = map->map_lst->content;
		if (tmp)
		{
			len = ft_strlen_safe(map->map[i]);
			if (len > 0 && map->map[i][len - 1] == '\n')
				map->map[i][len - 1] = 0;
		}
		i++;
		free(map->map_lst);
		map->map_lst = tmp;
	}
	map->map[i] = NULL;
	map->height = i;
}

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
			exit_error("Line too short!.");
		if (map->width != len)
			exit_error("Map with unequal line length.");
		if (ft_strspn(map->map[i], "01CEP") != map->width)
			exit_error("Map with wrong tile.");
		if (map->map[i][0] != '1' || map->map[i][len - 1] != '1')	
			exit_error("First or last column not only obstacles");
		map->exit_count += get_chars_count(map->map[i], "E");
		map->coin_count += get_chars_count(map->map[i], "C");
		map->player_count += get_chars_count(map->map[i], "P");
		i++;
	}
}

t_pos find_char_in_map(t_map *map, char c)
{
    int i;
	char *target;
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
	if (ft_strspn(map->map[0], "1") != map->width ||
		ft_strspn(map->map[map->height - 1], "1") != map->width)
			exit_error("First or last row not only obstacles.");
	if (map->exit_count != 1 || map->player_count != 1 ||
		map->coin_count < 1)
		exit_error("Wrong count of 'exit','player' or 'coin' tiles.");
	map->position = find_char_in_map(map, 'P');
	map->exit = find_char_in_map(map, 'E');
}

void	copy_map(t_map *map)
{
	int		i;

	i = 0;
	map->map_copy = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_copy)
		exit_error("You've ran out of memory!");
	while (map->map[i])
	{
		map->map_copy[i] = ft_strdup(map->map[i]);
		if (!map->map_copy[i])
			exit_error("You've ran out of memory!");
		i++;
	}
	map->map_copy[i] = NULL;
}

void	flood_fill(t_map *map, t_pos pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= (int)map->width ||
		pos.y >= (int)map->height || map->map_copy[pos.y][pos.x] == '1' ||
		map->map_copy[pos.y][pos.x] == 'X')
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
		exit_error("Not all coins are reachable!");
	if (map->exit_count != map->exit_total)
		exit_error("The exit isn't reachable!");
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_px / 8));
	*(unsigned int*)dst = color;
}

t_mlx_data	load_texture(t_map *map, char *path)
{
	t_mlx_data	img;

	img.img = mlx_xpm_file_to_image(map->mlx, path, &img.width, &img.height);
	if (!img.img)
		exit_error("Texture could not be loaded. Check file path!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_px, &img.line_length, &img.endian);
	return (img);
}

void load_all_textures(t_map *map)
{
    map->textures.collectible = load_texture(map, "./textures/collectible.xpm");
    map->textures.floor = load_texture(map, "./textures/floor.xpm");
    map->textures.p_e_floor = load_texture(map, "./textures/p_e_floor.xpm");
    map->textures.exit = load_texture(map, "./textures/exit.xpm");
    map->textures.player = load_texture(map, "./textures/player.xpm");
    map->textures.wall = load_texture(map, "./textures/wall.xpm");
}

void	render_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			mlx_put_image_to_window(map->mlx, map->mlx_win, map->textures.floor.img, j * TILE_SIZE, i * TILE_SIZE);
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(map->mlx, map->mlx_win, map->textures.wall.img, j * TILE_SIZE, i * TILE_SIZE);
			else if (map->map[i][j] == 'C')
				mlx_put_image_to_window(map->mlx, map->mlx_win, map->textures.collectible.img, j * TILE_SIZE, i * TILE_SIZE);
			else if (map->map[i][j] == 'P')
				mlx_put_image_to_window(map->mlx, map->mlx_win, map->textures.player.img, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}

}

void	move_player(t_map *map, t_pos new_pos)
{
	t_pos last;

	if (map->map[new_pos.y][new_pos.x] == '1')
		return ;
	last.x = map->position.x;
	last.y = map->position.y;
	if (new_pos.x == map->exit.x && new_pos.y == map->exit.y && map->exit_shown == true)
		exit(1) ;
	if (map->map[new_pos.y][new_pos.x] == 'C')
		map->coin_current++;
	if (map->coin_current == map->coin_total && map->exit_shown == false)
	{
		map->exit_shown = true;
		mlx_put_image_to_window(map->mlx, map->mlx_win, map->textures.exit.img, map->exit.y * TILE_SIZE, map->exit.x * TILE_SIZE);
	}
	map->map[last.y][last.x] = '0';
	map->map[new_pos.y][new_pos.x] = 'P';
	map->position = new_pos;
	map->moves++;
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->textures.floor.img, last.x * TILE_SIZE, last.y * TILE_SIZE);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->textures.player.img, new_pos.x * TILE_SIZE, new_pos.y * TILE_SIZE);
}

int	key_press_handler(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
		exit_error("Bye bye!");
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

int	main(int ac, char **av)
{
	t_map map;

	init_struct(&map);	
	check_args(ac, av);
	read_file_to_lst(av[1], &map.map_lst);
	lst_to_strs(&map);
	check_map_loop(&map);
	check_map_final(&map);
	copy_map(&map);
	flood_fill(&map, map.position);
	flood_fill_check(&map);
	
	map.mlx = mlx_init();
	map.mlx_win = mlx_new_window(map.mlx, map.width * TILE_SIZE, map.height * TILE_SIZE, "My first window");
	load_all_textures(&map);
	render_map(&map);
	mlx_hook(map.mlx_win, 2, (1L << 0), &key_press_handler, &map);

	mlx_loop(map.mlx);
}
