/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <gderoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:27:06 by gderoyan          #+#    #+#             */
/*   Updated: 2025/12/02 19:27:10 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

size_t	ft_strlen_safe(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	int		i;

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

static const char	*ft_strpbrk(const char *s, const char *accept)
{
	int		i;

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
