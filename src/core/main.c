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
	int fd = open(av[1], O_RDONLY);
	// TODO: read file into list
	t_list *map_lst = NULL;
	char *line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
				  break ;
		ft_lstadd_back(&map_lst, ft_lstnew(line));
	}


	// TODO: transform list to char**
	char **map = malloc(sizeof(char *) * (ft_lstsize(map_lst) + 1));
	if (!map)
		exit_error("Couldn't malloc for the **map.\n");
	int i = 0;
	t_list	*tmp;
	while (map_lst)
	{
		tmp = map_lst->next;
		map[i] = map_lst->content;
		i++;
		free(map_lst);
		map_lst = tmp;
	}
	map[i] = NULL;


	for (int i = 0; map[i]; i++)
		printf("%s", map[i]);
}
