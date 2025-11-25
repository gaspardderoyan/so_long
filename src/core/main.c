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

void	exit_error(char *msg)
{
	// TODO: add cleanup of memory
	printf("Error: %s\n", msg);
	exit(1);
}
void	check_args(int ac, char **av)
{
	char *last_dot;

	if (ac != 2)
		exit_error("Please provide exactly 1 .ber map.\n");
	last_dot = ft_strrchr(av[1], '.');
	if (strcmp(last_dot, ".ber"))
		exit_error("The map must be in .ber format.\n");
}

int	main(int ac, char **av)
{
	check_args(ac, av);
}
