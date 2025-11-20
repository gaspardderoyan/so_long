/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:36:49 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:36:49 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

/*
#include <stdio.h>
int	main(void)
{
	char str[] = "This is a test!";

	ft_bzero(str + 9, 2);
	printf("%s\n", str);
	printf("%s\n", str + 10);
	printf("%s\n", str + 11);
	return (0);
}
*/
