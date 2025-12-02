/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:59:18 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 19:24:42 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "./keys.h"
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# define TS 64

typedef enum e_tex_id
{
    TEX_WALL,
    TEX_FLOOR,
    TEX_PLAYER,
    TEX_COLL,
    TEX_EXIT,
    TEX_P_EXIT
}   t_tex_id;

typedef struct s_pos {
	int	x;
	int	y;
}	t_pos ;

typedef struct s_mlx_data {
	void	*img;
	void	*addr;
	int		bits_per_px;
	int		line_length;
	int		endian;
	int		width;
	int		height;
} t_mlx_data;

typedef struct s_textures {
	t_mlx_data	wall;	
	t_mlx_data	exit;	
	t_mlx_data	player;	
	t_mlx_data	collectible;	
	t_mlx_data	floor;	
	t_mlx_data	p_e_floor;	
} t_textures ;

typedef struct s_map {
	char	**map;
	char	**map_copy;
	t_list	*map_lst;
	size_t	width;
	size_t	height;
	size_t	coin_total;
	size_t	coin_count;
	size_t	coin_current;
	size_t	exit_total;
	size_t	exit_count;
	size_t	player_count;
	size_t	moves;
	t_pos	position;
	t_pos	exit;
	void	*mlx;
	void	*win;
	t_textures	textures;
}	t_map ;


/* utils_str */
size_t	ft_strlen_safe(char *str);
int	ft_strcmp(char *s1, char *s2);
size_t	ft_strspn(const char *s, const char *accept);
size_t	get_chars_count(const char *str, char *chars);

/* map_parsing */
void	check_args(int ac, char **av, t_map *map);
void	read_file_to_lst(char *filename, t_list **head, t_map *map);
void	lst_to_strs(t_map *map);

/* map_validation */
void	check_map_loop(t_map *map);
void	check_map_final(t_map *map);

/* map_flood_fill */
void	copy_map(t_map *map);
void	flood_fill(t_map *map, t_pos pos);
void	flood_fill_check(t_map *map);

/* init */
void	init_struct(t_map *map);
void	load_all_textures(t_map *map);

/* cleanup */
int	close_game(t_map *map);
void	exit_error(char *msg, t_map *map);

/* render */
void	render_sprite(t_map *m, t_pos pos, t_tex_id type);
void	render_map(t_map *map);

/* events */
int	key_press_handler(int keycode, t_map *map);

#endif
