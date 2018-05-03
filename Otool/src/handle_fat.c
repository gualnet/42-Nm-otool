/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:17:47 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 16:36:15 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

long	fat_swap_endian(long value)
{
	long	result;

	result = 0;
	result |= (value & 0x00000000000000FF) << 24;
	result |= (value & 0x000000000000FF00) << 8;
	result |= (value & 0x0000000000FF0000) >> 8;
	result |= (value & 0x00000000FF000000) >> 24;
	result |= (value & 0x000000FF00000000) << 24;
	result |= (value & 0x0000FF0000000000) << 8;
	result |= (value & 0x00FF000000000000) >> 8;
	result |= (value & 0xFF00000000000000) >> 24;
	return (result);
}

int		jump_to_exec(t_vault *vault, struct fat_arch *info)
{
	uint32_t			jumper;

	jumper = info->offset;
	vault->o_dump = offset_jumper(vault, vault->fat_dump, jumper);
	if (vault->o_dump == NULL)
		return (-1);
	return (1);
}

int		get_fat_cpu_type(t_vault *vault, unsigned long nbr_arch, char *path)
{
	unsigned long	i;
	struct fat_arch	*info;

	i = 0;
	info = vault->fat_dump + sizeof(struct fat_header);
	while (i < nbr_arch)
	{
		swap_info_data(info);
		if (CUR_CPU == "x86_64" && info->cputype == \
		(CPU_TYPE_I386 | CPU_ARCH_ABI64))
		{
			vault->file_nfo += M_64B;
			if (jump_to_exec(vault, info) == -1)
				return (-1);
			ft_printf("%s:\n", path);
			handle_64(vault);
			return (1);
		}
		info = (void*)info + sizeof(struct fat_arch);
		i++;
	}
	return (0);
}

int		handle_fat(t_vault *vault, char *path)
{
	struct fat_header	*header;
	unsigned long		nbr;
	int					ret;

	header = (void*)vault->fat_dump;
	nbr = fat_swap_endian(header->nfat_arch);
	if ((ret = get_fat_cpu_type(vault, nbr, path)) == -1)
		return (-1);
	if (ret != 1)
		ret = get_fat_cpu_type_else(vault, nbr, path);
	return (1);
}
