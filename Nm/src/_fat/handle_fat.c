/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:07:19 by galy              #+#    #+#             */
/*   Updated: 2018/04/04 12:37:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	jump_to_exec(t_vault *vault, struct fat_arch *info, unsigned long nbr)
{
	uint32_t				jumper;

	nbr = 0;
	jumper = (sizeof(struct fat_arch) * nbr) + swap_endian(info->offset);
	vault->f_dump = offset_jumper(vault, vault->ar_dump, jumper);
	vault->header = vault->f_dump;
}

void	get_fat_cpu_type(t_vault *vault, unsigned long nbr_arch)
{
	unsigned long	i;
	struct fat_arch	*info;

	i = 0;
	info = vault->ar_dump + sizeof(struct fat_header);

	// print_offset(vault, info);
	
	while (i < nbr_arch)
	{
		if (CUR_CPU == "x86_64" && swap_endian(info->cputype) == \
		(CPU_TYPE_I386 | CPU_ARCH_ABI64))
		{
			jump_to_exec(vault, info, nbr_arch - i);
			handle_64bits(vault);
			break;
		}
 
		info = (void*)info + sizeof(struct fat_arch);
		i++;
	}
}

void	handle_fat(t_vault *vault)
{
	struct fat_header	*header;
	unsigned long		nbr;

	vault->ar_dump = vault->f_dump;
	vault->f_dump = NULL;
	header = vault->ar_dump;
	nbr = swap_endian(header->nfat_arch);
	get_fat_cpu_type(vault, nbr);
}
