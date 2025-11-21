/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyqn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:38:54 by gderoyqn          #+#    #+#             */
/*   Updated: 2024/12/12 17:38:56 by gderoyqn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	strlen_safe(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dst, char *src)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] || s[i] == '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*ptr;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	ptr = dest;
	while (i < n)
	{
		*(char *)dest = *(char *)src;
		dest++;
		src++;
		i++;
	}
	return (ptr);
}

/* joins line & buffer into new string, frees old line
 * if nl_char exists, only copies up to & including newline
 * otherwise copies entire buffer content */
char	*join_lnb(char **line, char *buffer, char *nl_char)
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
