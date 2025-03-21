#include "../libft/inc/libft.h"
#include "../inc/so_long.h"

// TODO: move to libft
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

// TODO: move to libft
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

static t_master	*init_master()
{
	t_master	*master;
	master = ft_calloc(1, sizeof(t_master));
	if (!master)
		return (NULL) ;
	master->start = ft_calloc(1, sizeof(t_position));
	if (!master->start)
		return (free(master), NULL);
	master->lines = 0;
	master->len = 0;
	master->map = NULL;
	master->char_map = NULL;
	return (master);
}


static void	check_line(char *line, u_int8_t *found)
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
static bool	check_map(t_list *char_map, size_t lines)
{
	size_t		first_len;
	size_t		i;
	u_int8_t	found;
	
	first_len = strlen_safe(char_map->content);
	if (ft_strspn(char_map->content, "1") != first_len - 1
		|| ft_strspn(ft_lstlast(char_map)->content, "1") != first_len - 1)
			   return (ft_printf("First or last line not walls!\n"), false);
	i = 0;
	found = 0;
	while (char_map)
	{
		if (strlen_safe(char_map->content) != first_len)
			return (ft_printf("Not a rectangle!\n"), false);
		if (i != 0 && i != lines - 1 && (((char *)(char_map->content))[0] != '1'
			|| ((char *)(char_map->content))[first_len - 2] != '1'))
			   return (ft_printf("First or last char not wall!\n"), false);
		check_line(char_map->content, &found);
		char_map = char_map->next;
		i++;
	}
	if (found != 3)
		return (ft_printf("Invalid count of exit/start cells\n", found), false);
	return (true);
}

bool	process_map(int	fd, t_master *master)
{
	char	*res;

	master = init_master();
	res = NULL;
	if (!master)
		return (ft_printf("Master struct initialisation failed!\n"), false);
	while (master->lines == 0 || res)
	{
		res = get_next_line(fd);
		if (!res)
			break ;
		ft_lstadd_back(&master->char_map, ft_lstnew(res));
		master->lines++;
	}
	if (!check_map(master->char_map, master->lines))
		return (ft_printf("Map not OK\n"), ft_lstfree(master->char_map), close(fd), false);
	return (ft_printf("First map check OK\n"), true);
}
