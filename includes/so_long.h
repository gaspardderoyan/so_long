/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:59:18 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/28 23:07:44 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# define TILE_SIZE 64

typedef struct s_pos {
	size_t	x;
	size_t	y;
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
	size_t	exit_total;
	size_t	coin_count;
	size_t	exit_count;
	size_t	player_count;
	t_pos	start;
	void	*mlx;
	void	*mlx_win;
	t_textures	textures;
}	t_map ;

#endif
