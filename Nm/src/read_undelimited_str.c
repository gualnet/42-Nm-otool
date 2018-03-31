/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_undelimited_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 20:50:48 by galy              #+#    #+#             */
/*   Updated: 2018/03/30 16:28:44 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
		{
			// ft_putchar('*');
			break;
		}
		ft_printf("%c", ptr[i]);
		i++;
	}
	// ft_putchar('\n');
}