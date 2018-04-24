/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 20:53:28 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:23:09 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		to_exit(t_vault *vault)
{

	//free le vault..
	if (vault == NULL)
		return (0);
	if (vault->f_dump != NULL)
		munmap(vault->f_dump, vault->f_stat.st_size);
	ft_printf("TO EXIT(func)\n");
	return (-1);
}