#include "../libft/inc/libft.h"
#include "../inc/so_long.h"

void	print_map(u_int8_t **map, bool free_map)
{
	int	i;
	int	j;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_printf("%d", map[i][j]);
			j++;
		}
		ft_printf("\n");
		if (free_map)
			free(map[i]);
		i++;
	}
	if (free_map)
		free(map);
}




int main(int ac, char **av)
{
	int			fd;
	t_master	*master;

	if (ac != 2)
		return(ft_printf("Wrong number of args! Please provide 1 .ber map\n"), 0);
	if (ft_strnstr(av[1], ".ber", strlen_safe(av[1])) == NULL)
		return(ft_printf("Map must have the .ber extension!"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd <= -1)
		return (ft_printf("Error opening file!\n"), 1);

	master = init_master();
	process_map(fd, master);

	master->map = convert_map(master->char_map, master->lines, master->start);
	if (bfs(master->map, master->start))
		printf("BFS OK!\n");
	else
		printf("BFS KO :(\n");
	print_map(master->map, false);
	return (ft_lstfree(master->char_map), close(fd), 0);
}
