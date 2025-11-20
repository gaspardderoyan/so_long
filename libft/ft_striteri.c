/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:44:31 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:44:31 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;	

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*
void	ft_to_index(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c = i + '0';
}
int	main(void)
{
	char str[] = "A test!";
	printf("Before: %s\n", str);
	ft_striteri(str, &ft_to_index);
	printf("After: %s\n", str);
	return (0);
}
*/
