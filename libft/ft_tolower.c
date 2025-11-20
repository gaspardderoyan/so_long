/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:42:06 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:42:06 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ' ');
	return (c);
}

/*
#include <stdio.h>
int	main(void)
{
	char	c;
	c = 'A';
	printf("char: %c", ft_tolower(c));
	return (0);
}
*/
