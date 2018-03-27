/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_undelimited_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 20:50:48 by galy              #+#    #+#             */
/*   Updated: 2018/03/26 21:00:30 by galy             ###   ########.fr       */
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
		ft_putchar(ptr[i]);
		i++;
	}
	ft_putchar('\n');
}