/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect_dump_32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:46:00 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 12:12:51 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_off_32(t_vault *vault, unsigned long cpt)
{
	off_t			adr;
	struct section	*sect_hdr;

	sect_hdr = vault->sect_hdr;
	adr = sect_hdr->addr;
	if ((vault->file_nfo & M_32B) == M_32B)
		ft_printf("%.8x%c", adr + cpt, '\t');
	else
		ft_printf("\nHEUK !!\n");
}

void	print_sect_dump_32(t_vault *vault)
{
	struct section	*sect_hdr;
	unsigned long	i;
	unsigned long	cpt;

	i = 0;
	cpt = 0;
	sect_hdr = vault->sect_hdr;
	vault->sect = offset_jumper(vault, vault->o_dump, sect_hdr->offset);
	ft_printf("Contents of (%s,%s) section\n", sect_hdr->segname, sect_hdr->sectname);
	while (cpt < sect_hdr->size && vault->sect != NULL)
	{
		if (cpt != 0 && (cpt % 16) == 0)
			ft_printf("\n");
		if ((cpt % 16) == 0)
			print_off_32(vault, cpt);
		ft_printf("%0.2hhx ", *(char*)(vault->sect + cpt));
		
		i++;
		cpt = i * sizeof(char);
	}
	ft_printf("\n");
}
