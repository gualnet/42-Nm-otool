/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:17:47 by galy              #+#    #+#             */
/*   Updated: 2018/04/12 15:32:38 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

long	fat_swap_endian(long value)
{
	long	result;

	result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

int		jump_to_exec(t_vault *vault, struct fat_arch *info)
{
	uint32_t			jumper;
	
	vault->file_nfo += M_64B;
	jumper = fat_swap_endian(info->offset);

	vault->o_dump = offset_jumper(vault, vault->fat_dump, jumper);
	if (vault->o_dump == NULL)
		return (-1);
	return (1);
}

int		get_fat_cpu_type(t_vault *vault, unsigned long nbr_arch)
{
	unsigned long		i;
	struct	fat_arch	*info;

	i = 0;
	info = vault->fat_dump + sizeof(struct fat_header);
	while (i < nbr_arch)
	{
		if (CUR_CPU == "x86_64" && fat_swap_endian(info->cputype) == \
		(CPU_TYPE_I386 | CPU_ARCH_ABI64))
		{
			if (jump_to_exec(vault, info) == -1)
				return (-1);
			handle_64(vault);
			return (1);
		}
		info = (void*)info + sizeof(struct fat_arch);
		i++;
	}
	return (0);
}

int		handle_fat(t_vault *vault)
{
	// ft_printf("Call handle_64 %p\n\n", vault);
	struct fat_header	*header;
	unsigned long		nbr;
	int					ret;
	
	header = (void*)vault->fat_dump;
	nbr = fat_swap_endian(header->nfat_arch);
	// si le fat contient l'obj du meme type que le cpu - 
	// la func return (1).
	// si la func return (0) architecture du systeme n'est pas
	//	presente dans l'archive/fat.
	if ((ret = get_fat_cpu_type(vault, nbr)) == -1)
		return (-1);
	if (ret != 1)
	{
		ft_printf("\nhandle_fat.c need more function\n");
		//need a func to print everything..
		exit (-1);
	}

	return (1);
}