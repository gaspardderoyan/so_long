/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:59:18 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/28 22:48:27 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

typedef struct s_map {
	char	**map;
	t_list	*map_lst;
	int		width;
	int		height;
	int		coin_total;
	int		coin_count;
	int		exit_count;
	int		player_count;
} t_map ;
