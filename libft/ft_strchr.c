/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:41:40 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:41:40 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*
#include <stdio.h>
int	main(void)
{
	char	*ptr;
	ptr = ft_strchr("teste", 1024);
	if (ptr)
	{
		printf("The char's address found was %p\n", (void *)ptr);
		printf("The char - 1 found was %c\n", *(ptr - 1));
	}
	else
		printf("Returned NULL");
	return (0);
}
*/
