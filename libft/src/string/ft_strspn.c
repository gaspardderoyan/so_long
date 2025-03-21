#include "../../inc/libft.h"

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
