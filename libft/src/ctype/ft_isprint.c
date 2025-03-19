/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyqn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:17:58 by gderoyqn          #+#    #+#             */
/*   Updated: 2024/12/04 12:30:39 by gderoyqn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/libft.h"

int	ft_isprint(int c)
{
	if ((c >= 0 && c <= 31) || c >= 127 || c == EOF)
		return (0);
	return (1);
}
