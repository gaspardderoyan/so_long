/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:01:45 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/28 23:05:39 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	int		i;
	int		j;
	bool	found;

	i = 0;
	if (!s || !accept)
		return (0);
	while (s[i])
	{
		if (ft_strchr(accept, s[i]) == NULL)
			break ;
		i++;
	}
	return (i);
}

const char	*ft_strpbrk(const char *s, const char *accept)
{
	int		i;
	int		j;
	bool	found;

	i = 0;
	if (!s || !accept)
		return (NULL);
	while (s[i] && ft_strchr(accept, s[i]) == NULL)
		i++;
	if (!s[i])
		return (NULL);
	return (&s[i]);
}

/**
 * @brief Counts the total occurrences of specific characters in a string.
 *
 * Scans the input string `str` and calculates how many times any character
 * contained in the delimiter string `chars` appears.
 *
 * @param str The string to be scanned (Haystack).
 * @param chars A string containing the characters to count (Needles).
 * @return size_t The total count of matching characters found.
 * Returns 0 if either input is NULL.
 */
size_t	get_chars_count(const char *str, char *chars)
{
	size_t	count;

	count = 0;
	if (!str || !chars)	
		return (0);
	while (1)
	{
		str = ft_strpbrk(str, chars);
		if (!str)
			break ;
		str++;
		count++;
	}
	return (count);
}

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

void	init_struct(t_map *map)
{
	map->coin_count = 0;
	map->exit_count = 0;
	map->player_count = 0;
	map->coin_total = 0;
	map->height = 0;
	map->width = 0;
	map->map = NULL;
	map->map_lst = NULL;
}

void	read_file_to_lst(char *filename, t_list **head)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Error opening file!");
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

	map->map = malloc(sizeof(char *) * (ft_lstsize(map->map_lst) + 1));
	if (!map->map)
		exit_error("Couldn't malloc for the **map.\n");
	i = 0;
	while (map->map_lst)
	{
		tmp = map->map_lst->next;
		map->map[i] = map->map_lst->content;
		i++;
		free(map->map_lst);
		map->map_lst = tmp;
	}
	map->map[i] = NULL;
	map->height = i;
}

void	check_map(t_map *map)
{
	size_t	i;
	int		len;

	i = 0;
	map->width = ft_strlen(map->map[0]);
	while (map->map[i])
	{
		len = ft_strlen(map->map[i]);
		if (len == 0)
			exit_error("Line too short!.\n");
		if (map->width != len)
			exit_error("Map with unequal line length.\n");
		if (map->map[i][0] != '1' || map->map[i][len - 1] != '1')	
			exit_error("First or last column not only obstacles");
		map->exit_count += get_chars_count(map->map[i], "E");
		map->coin_count += get_chars_count(map->map[i], "C");
		map->player_count += get_chars_count(map->map[i], "P");
		i++;
	}
	if (ft_strspn(map->map[0], "!") != map->width ||
		ft_strspn(map->map[map->height - 1], "!") != map->width)
			exit_error("First or last row not only obstacles.");
	if (map->exit_count != 1 || map->player_count != 1 ||
		map->coin_count < 1)
		exit_error("Wrong count of 'exit','player' or 'coin' tiles.");

}

int	main(int ac, char **av)
{
	t_map map;

	init_struct(&map);	
	check_args(ac, av);
	read_file_to_lst(av[1], &map.map_lst);
	lst_to_strs(&map);
	check_map(&map);
	for (int i = 0; map.map[i]; i++)
		printf("%s", map.map[i]);

}
