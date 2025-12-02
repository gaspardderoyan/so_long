/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:59:18 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 18:30:32 by gderoyan         ###   ########.fr       */
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

#endif
