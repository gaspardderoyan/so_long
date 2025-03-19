/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderoyqn <gderoyqn@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 02:51:18 by gderoyqn          #+#    #+#             */
/*   Updated: 2025/01/21 02:51:36 by gderoyqn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isspace(int c)
{
	const unsigned char	cc = (unsigned char)c;

	return ((cc >= 9 && cc <= 13) || cc == 32);
}
