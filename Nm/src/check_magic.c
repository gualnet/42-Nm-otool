/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:10:59 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:19:23 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int Magic_32_64(t_vault *vault)
{
	unsigned int magic_num;
	char *test;
	int nok;

	nok = 0;
	magic_num = *(unsigned int *)vault->f_dump;
	test = vault->f_dump;
	if (magic_num == MH_MAGIC_64 || magic_num == MH_CIGAM_64)
		vault->file_nfo = M_64B;
	else if (magic_num == MH_MAGIC || magic_num == MH_CIGAM)
		vault->file_nfo = M_32B;
	else if (ft_strncmp(ARMAG, test, SARMAG) == 0)
		vault->file_nfo = M_ARCH;
	else if (magic_num == FAT_MAGIC || magic_num == FAT_CIGAM)
		vault->file_nfo = M_FAT;
	else
		nok = 1;
	if (magic_num == MH_CIGAM || magic_num == MH_CIGAM_64)
		vault->file_nfo += M_SWAP_ENDIAN;
	if (nok == 1)
		return (-1);
	return (1);
}

/*
**	if the MAGIC is 64 bit
**	assigne a 64bit header to the dumped data
**	else the programme stop..
*/

int	check_magic_num(t_vault *vault)
{
	size_t header_size;
	
	header_size = -1;
	if ((Magic_32_64(vault)) == -1)
		return (-1);
	vault->header = vault->f_dump;
	return (1);	
}
