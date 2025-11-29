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

#include "libft.h"

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
