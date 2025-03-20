#include "../libft/inc/libft.h"
#include <stddef.h>
#include <sys/types.h>

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

/**
 * @brief calculate the len of the initial segment of 's' which contains only
 * chars from 'accept'
 */
size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	len;

	len = 0;
	while (s && *s)
	{
		if (ft_strchr(accept, *s))
			len++;
		s++;
	}
	return (len);
}

void	check_line(char *line, u_int8_t *found)
{
	while (line && *line)
	{
		if ((*found & 1 && *line == 'E') || (*found & 2 && *line == 'P'))
			*found |= 4;
		else if (*line == 'E')
			*found |= 1;
		else if (*line == 'P')
			*found |= 2;
		line++;
	}
}

/**
 * @brief check if the map is valid
 *
 * @return true if it is, false if not valid
 *
 * compare strspn with len - 1 to account for the \n at the end
 */
bool	check_map(t_list *char_map, size_t lines)
{
	size_t		first_len;
	size_t		i;
	u_int8_t	found;
	
	first_len = strlen_safe(char_map->content);
	if (ft_strspn(char_map->content, "1") != first_len - 1
		|| ft_strspn(ft_lstlast(char_map)->content, "1") != first_len - 1)
			   return (ft_printf("First or last line not walls!\n", false));
	i = 0;
	while (char_map)
	{
		if (strlen_safe(char_map->content) != first_len)
			return (ft_printf("Not a rectangel!"), false);
		if (i != 0 && i != lines - 1 && (((char *)(char_map->content))[0] != '1'
			|| ((char *)(char_map->content))[first_len - 2] != '1'))
			   return (ft_printf("First or last char not wall!\n"), false);
		check_line(char_map->content, &found);
		char_map = char_map->next;
		i++;
	}
	if (found != 3)
		return (ft_printf("Invalid count of exit or start cells: %d\n", found), false);
	return (true);
}

#include <fcntl.h>
int main(int ac, char **av)
{
	int		fd;
	size_t	lines;
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
	if (!check_map(char_map, lines))
		ft_printf("Map not OK\n");
	else
		ft_printf("Map is valid :)\n");
	return (ft_lstfree(char_map), close(fd), 0);
}
