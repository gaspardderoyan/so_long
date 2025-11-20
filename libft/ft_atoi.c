/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:36:47 by gderoyan          #+#    #+#             */
/*   Updated: 2025/11/11 11:36:47 by gderoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	pola;

	n = 0;
	pola = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		nptr++;
		pola = -1;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		n += (char)*nptr - '0';
		if (ft_isdigit(*(nptr + 1)))
			n *= 10;
		nptr++;
	}
	return (n * pola);
}

/*
int	main(void)
{
	const char str[] = "--1";
	int	n;
	n = ft_atoi(str);
	printf("Res: %d\n", n);
	return (0);
}
*/
