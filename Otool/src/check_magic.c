/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:26:19 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 15:40:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		magic_32_64(t_vault *vault)
{
	unsigned int	magic_num;
	char			*test;
	int				nok;

	nok = 0;
	magic_num = *(unsigned int *)vault->fat_dump;
	test = (vault->fat_dump != NULL) ? vault->fat_dump : "";
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

int		check_magic_num(t_vault *vault)
{
	size_t header_size;

	header_size = -1;
	if ((magic_32_64(vault)) == -1)
		return (-1);
	return (1);
}
