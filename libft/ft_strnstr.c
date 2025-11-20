/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:42:43 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:42:43 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] && little[j]
				&& (i + j) < len && big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	char	haystack[30] = "aaabcabcd";
	//char	needle[10] = "aabc";
	//char	*empty = (char *)"";
	char	*res;
	res = NULL;
	res = ft_strnstr(haystack, "a", 1);
	if (res)
		printf("res: %s", res);
	else
		printf("res is NULL");
	return (0);
}
*/
