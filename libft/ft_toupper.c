/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:40:49 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:40:49 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ' ');
	return (c);
}

/*
#include <stdio.h>
int	main(void)
{
	char	c;
	c = 'a';
	printf("char: %c", ft_toupper(c));
	return (0);
}
*/
