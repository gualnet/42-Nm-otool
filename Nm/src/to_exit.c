/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 20:53:28 by galy              #+#    #+#             */
/*   Updated: 2018/03/31 03:45:26 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	to_exit(t_vault *vault)
{

	//free le vault..
	if (vault == NULL)
		exit(-1);
	if (vault->f_dump != NULL)
		munmap(vault->f_dump, vault->f_stat.st_size);

	exit(EXIT_FAILURE);
}