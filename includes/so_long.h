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

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

typedef struct s_pos {
	int	x;
	int	y;
}	t_pos ;

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
}	t_map ;
