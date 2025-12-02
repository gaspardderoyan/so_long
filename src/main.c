/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:01:45 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 19:24:20 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_map	m;

	init_struct(&m);
	check_args(ac, av, &m);
	read_file_to_lst(av[1], &m.map_lst, &m);
	lst_to_strs(&m);
	check_map_loop(&m);
	check_map_final(&m);
	copy_map(&m);
	flood_fill(&m, m.position);
	flood_fill_check(&m);
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, m.width * TS, m.height * TS, "./so_long");
	load_all_textures(&m);
	render_map(&m);
	mlx_hook(m.win, 2, (1L << 0), &key_press_handler, &m);
	mlx_hook(m.win, 17, 0, close_game, &m);
	mlx_loop(m.mlx);
}
