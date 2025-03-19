#include "../libft/inc/libft.h"
#include <stddef.h>

enum Cell {
	EMPTY,
	WALL,
	COIN,
	EXIT,
	START
};

void	ft_lstfree(t_list *lst)
{
	t_list *temp;

	temp = NULL;
	while(lst)
	{
		temp = lst;	
		lst = lst->next;
		free(temp->content);
		free(temp);
	}
}

bool	check_map(t_list *char_map, int lines)
{
	size_t		first_len;
	u_int8_t	found;
	
	first_len = strlen_safe(char_map->content);
	// TODO: if first or last lines not all WALL, false
	while (char_map)
	{
		if (strlen_safe(char_map->content) != first_len)
			return (ft_printf("Not a rectangel!"), false);
		// TODO: if first and last char of each line != WALL, false
		// TODO: if START, found OR 1 ; if END, found OR 3 
		char_map = char_map->next;
	}
	// TODO: if found != 3, false
	return (true);
}

#include <fcntl.h>
int main(int ac, char **av)
{
	int		fd;
	int		lines;
	char	*res;
	t_list	*char_map;

	if (ac != 2)
		return(ft_printf("Wrong number of args! Please provide 1 .ber map\n"), 0);
	if (ft_strnstr(av[1], ".ber", strlen_safe(av[1])) == NULL)
		return(ft_printf("Map must have the .ber extension!"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd <= -1)
		return (ft_printf("Error opening file!\n"), 1);
	lines = 0;
	res = NULL;
	char_map = NULL;
	while (lines == 0 || res)
	{
		res = get_next_line(fd);
		if (!res)
			break ;
		ft_printf("Line %d: %s", lines, res);
		ft_lstadd_back(&char_map, ft_lstnew(res));
		lines++;
	}
	if (!check_map(char_map))
		break ;
	return (ft_lstfree(char_map), close(fd), 0);
}
