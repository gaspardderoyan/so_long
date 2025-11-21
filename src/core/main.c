/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:01:45 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/21 16:25:14 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

bool	check_args(int ac, char **av)
{
	char *last_dot;

	if (ac != 2)
		return (printf("Please provide exactly 1 .ber map.\n"), true);
	last_dot = ft_strrchr(av[1], '.');
	if (strcmp(last_dot, ".ber"))
		return (printf("The map must be in .ber format.\n"), true);
	return (false);
}

int	main(int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
}
