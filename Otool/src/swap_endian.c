/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_endian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:46:16 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:39:11 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	    swap_endian(int value)
{
	int	result;

	result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

long    swap_long_endian(long value)
{
	long	result;

	result = 0;
    result |= (value & 0x000000FF00000000) << 24;
    result |= (value & 0x0000FF0000000000) << 8;
    result |= (value & 0x00FF000000000000) >> 8;
    result |= (value & 0xFF00000000000000) >> 24;
	result |= (value & 0x00000000000000FF) << 24;
    result |= (value & 0x000000000000FF00) << 8;
    result |= (value & 0x0000000000FF0000) >> 8;
    result |= (value & 0x00000000FF000000) >> 24;
    return result;
}
