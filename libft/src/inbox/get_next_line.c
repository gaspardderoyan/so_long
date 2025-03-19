/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyqn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:36:49 by gderoyqn          #+#    #+#             */
/*   Updated: 2024/12/14 16:21:15 by gderoyqn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*join_lnb(char **line, char *buffer, char *nl_char)
{
	size_t	line_len;
	size_t	buf_len;
	char	*new_line;

	line_len = strlen_safe(*line);
	if (nl_char)
		buf_len = (size_t)(nl_char - buffer + 1);
	else
		buf_len = strlen_safe(buffer);
	new_line = (char *)malloc(sizeof(char) * (line_len + buf_len + 1));
	if (!new_line)
		return (NULL);
	if (*line)
		ft_memcpy(new_line, *line, line_len);
	ft_memcpy(new_line + line_len, buffer, buf_len);
	new_line[line_len + buf_len] = '\0';
	free(*line);
	*line = NULL;
	return (new_line);
}

static void	read_loop(char *buffer, char **line, int fd)
{
	int		bytes_read;
	char	*nl_char;

	while (1)
	{
		nl_char = ft_strchr(buffer, '\n');
		*line = join_lnb(line, buffer, nl_char);
		if (nl_char)
		{
			ft_strcpy(buffer, nl_char + 1);
			break ;
		}
		buffer[0] = '\0';
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
			buffer[bytes_read] = 0;
		else if (bytes_read == 0)
			break ;
		else
		{
			buffer[0] = 0;
			break ;
		}
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	read_loop(buffer, &line, fd);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int		fd;
	int		i;
	char	*res;

	fd = open("test.txt", O_RDONLY);
	if (fd <= -1)
	{
		printf("Error opening file!\n");
		return (1);
	}

	i = 0;
	while (i < 50)
	{
		res = get_next_line(fd);
		if (!res)
			break ;
		printf("%s", res);
		free(res);
		i++;
	}

	return (0);
}
*/
