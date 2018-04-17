/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ppc_in_fat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:46:07 by galy              #+#    #+#             */
/*   Updated: 2018/04/17 14:07:30 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"


void	*dump_endian_reverse_ppc(t_vault *vault, size_t size)
{
	size_t 	i;
	void	*dump;
	void 	*tete;
	void	*ppc;
	
	i = 0;
	tete = NULL;
	if ((dump = malloc(size)) == NULL)
		return (NULL);
	ppc = vault->f_dump;
	ft_bzero(dump, size);
	while (i * 4 < size)
	{
		ft_printf("[%d / %d]\n", i*4, size);
		*(int*)(dump + (int)tete) = swap_endian(*(int*)(ppc + (int)tete));
		tete += sizeof(int);
		i++;
	}
	ft_printf("0002\n");
	return (dump);
}

int		handle_ppc_in_fat(t_vault *vault, char *path, struct fat_arch *info)
{
	ft_printf("CALL PPC IN FAT [%p]\n", info);
	// ft_printf("vault->ar_dump [%p]\n", vault->ar_dump);
	// ft_printf("vault->f_dump [%p]\n", vault->f_dump);
	// ft_printf("info [%p]\n", info);
	// void	*rev_dump;
	// void	*tmp;

	// if ((rev_dump = dump_endian_reverse_ppc(vault, swap_endian(info->size))) == NULL)
	// 	return (-1);
	// tmp = vault->f_dump;
	// vault->f_dump = rev_dump;
	if (iter_cmds_ppc(vault) == -1)
		return (-1);
	ft_printf("\n%s (for architecture ppc):\n", path);
	if (display_list_ppc(vault) == -1)
		return (-1);
	// free(vault->f_dump);
	// vault->f_dump = tmp;
	return (1);
}