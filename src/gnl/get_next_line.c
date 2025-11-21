/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyqn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:36:49 by gderoyqn          #+#    #+#             */
/*   Updated: 2025/11/17 18:56:29 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* frees line & resets buffer when malloc fails or read errors */
static void	cleanup_line(char **line, char *buffer)
{
	if (*line)
		free(*line);
	*line = NULL;
	buffer[0] = 0;
}

/* joins buffer to line, handles newline placement
 * returns 0 if malloc fails, 1 on success */
static int	process_buffer(char **line, char *buffer, char *nl_char)
{
	char	*temp;

	temp = join_lnb(line, buffer, nl_char);
	if (!temp)
	{
		cleanup_line(line, buffer);
		return (0);
	}
	*line = temp;
	if (nl_char)
		ft_strcpy(buffer, nl_char + 1);
	return (1);
}

/* reads from fd into buffer, null-terminates it
 * returns num of bytes read (0 = EOF, -1 = error) */
static int	handle_read(char *buffer, int fd)
{
	int	bytes_read;

	buffer[0] = '\0';
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
		buffer[bytes_read] = 0;
	return (bytes_read);
}

/* main loop - keeps reading & building line until newline or EOF
 * handles malloc failures & read errors by cleaning up */
static void	read_loop(char *buffer, char **line, int fd)
{
	int		bytes_read;
	char	*nl_char;

	while (1)
	{
		nl_char = ft_strchr(buffer, '\n');
		if (!process_buffer(line, buffer, nl_char))
			return ;
		if (nl_char)
			break ;
		bytes_read = handle_read(buffer, fd);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
		{
			cleanup_line(line, buffer);
			return ;
		}
	}
}

/* returns next line from fd, or NULL if done/error
 * uses static buffer to remember leftover data between calls */
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	read_loop(buffer, &line, fd);
	if (!line || !*line)
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
