/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:10:59 by galy              #+#    #+#             */
/*   Updated: 2018/04/17 10:36:21 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int Magic_32_64(t_vault *vault)
{
	// ft_printf("MH_MAGIC_64 [%x]\n", MH_MAGIC_64);
	unsigned int magic_num;
	char *test;
	int nok;

	nok = 0;
	magic_num = *(unsigned int *)vault->f_dump;
	// ft_printf("magic==[%x][%x]\n", *(unsigned int *)vault->f_dump, magic_num);
	test = vault->f_dump;
	// ft_printf("LAAAA %x/%d\n\n", ARMAG, ft_strncmp(ARMAG, test, SARMAG));
	if (magic_num == MH_MAGIC_64 || magic_num == MH_CIGAM_64)
	{
		// ft_printf("==> struct 64bit\n");
		vault->file_nfo = M_64B;
	}
	else if (magic_num == MH_MAGIC || magic_num == MH_CIGAM)
	{
		// ft_printf("==> struct 32bit\n");
		vault->file_nfo = M_32B;
	}
	else if (ft_strncmp(ARMAG, test, SARMAG) == 0)
	{
		// ft_printf("==> struct arch\n");
		vault->file_nfo = M_ARCH;
	}
	else if (magic_num == FAT_MAGIC || magic_num == FAT_CIGAM)
	{
		// ft_printf("==> struct FAT\n");
		vault->file_nfo = M_FAT;
	}
	else
		nok = 1;
	if (magic_num == MH_CIGAM || magic_num == MH_CIGAM_64)
	{
		// ft_printf("==> struct swap endian\n");
		vault->file_nfo += M_SWAP_ENDIAN;
	}
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
	// ft_printf("\nCALL CHECK MAGIC NUM\n");
	size_t header_size;
	
	header_size = -1;
	if ((Magic_32_64(vault)) == -1)
		return (-1);
	// if (vault->file_nfo == 0x01 || vault->file_nfo == 0x05)
	// 	header_size = sizeof(struct mach_header);
	// else if (vault->file_nfo == 0x02 || vault->file_nfo == 0x06)
	// 	header_size = sizeof(struct mach_header_64);
	// else if (vault->file_nfo == 0x10 || vault->file_nfo == 0x14)
	// 	header_size = sizeof(struct fat_header);
	// if (vault->file_nfo == 0x08)
	// 	return (1);
	// if (header_size < 1 || (vault->header = malloc(header_size)) == NULL)
	// 	return (-1);
	// ft_memcpy(vault->header, vault->f_dump, header_size);
	vault->header = vault->f_dump;
	return (1);	
}
