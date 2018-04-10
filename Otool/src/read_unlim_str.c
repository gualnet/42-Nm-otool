/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_unlim_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 20:50:48 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 10:42:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	read_undelimited_str(char *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (ptr[i] == '\n')
		{
			ft_printf("\n read_undelimited_str ??\n");
			exit(-1);
		}
		if (ptr[i] <= 0x20)
			break;
		ft_printf("%c", ptr[i]);
		i++;
	}
}