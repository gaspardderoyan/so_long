/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:43:17 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:43:17 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

/*
#include <stdio.h>
int	main(void)
{
	const char str[] = "Test";
	size_t i = 0;
	i = ft_strlen(str);
	printf("This should be 4 --> %zu\n", i);
	return (0);
}
*/
