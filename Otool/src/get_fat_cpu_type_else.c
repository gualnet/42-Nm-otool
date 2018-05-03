/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fat_cpu_type_else.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:37:23 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 15:56:21 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	swap_info_data(struct fat_arch *info)
{
	info->cputype = swap_long_endian(info->cputype);
	info->cpusubtype = swap_long_endian(info->cpusubtype);
	info->offset = swap_long_endian(info->offset);
	info->size = swap_long_endian(info->size);
	info->align = swap_long_endian(info->align);
}

int		get_fat_cpu_type_else(t_vault *vault, \
unsigned long nbr_arch, char *path)
{
	struct fat_arch	*info;
	unsigned long	i;

	i = 0;
	info = offset_jumper(vault, vault->fat_dump, sizeof(struct fat_header));
	while (i < nbr_arch)
	{
		if (info == NULL)
			return (-1);
		if (info->cputype > 255)
			swap_info_data(info);
		if (jump_to_exec(vault, info) == -1)
			return (-1);
		if (info->cputype == CPU_TYPE_I386 && handle_32_fat(vault, path) == -1)
			return (-1);
		if (info->cputype == CPU_TYPE_POWERPC && \
		handle_ppc_fat(vault, path) == -1)
			return (-1);
		if ((info = offset_jumper(vault, info, sizeof(struct fat_arch))) \
		== NULL)
			return (-1);
		i++;
	}
	return (-1);
}
