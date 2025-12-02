#include "../includes/so_long.h"

void	check_args(int ac, char **av, t_map *map)
{
	char	*last_dot;

	if (ac != 2)
		exit_error("Please provide exactly 1 .ber map.", map);
	last_dot = ft_strrchr(av[1], '.');
	if (!last_dot || ft_strcmp(last_dot, ".ber"))
		exit_error("The map must be in .ber format.", map);
}

void	read_file_to_lst(char *filename, t_list **head, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Error opening file!", map);
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
		exit_error("Couldn't malloc for the **map.", map);
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
