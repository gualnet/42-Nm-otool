/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect_dump_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:57:35 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 12:12:12 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_off(t_vault *vault, unsigned long cpt)
{
	off_t				adr;
	struct section_64	*sect_hdr;

	sect_hdr = vault->sect_hdr;
	adr = sect_hdr->addr;
	// ft_printf("%.16lx %-8c", adr + cpt, ' ');
	// ft_printf("vault->file_nfo [%x][%b]\n",vault->file_nfo,vault->file_nfo);
	// ft_printf("M_64B [%x][%b]\n",M_64B,M_64B);
	if ((vault->file_nfo & M_64B) == M_64B)
		ft_printf("%.16lx%c", adr + cpt, '\t');
	else
		ft_printf("\nHEUK !!\n");
}

void	print_sect_dump_64(t_vault *vault)
{
	struct section_64	*sect_hdr;
	unsigned long		i;
	unsigned long		cpt;

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
			print_off(vault, cpt);
		ft_printf("%0.2hhx ", *(char*)(vault->sect + cpt));
		
		i++;
		cpt = i * sizeof(char);
	}
	ft_printf("\n");
}
