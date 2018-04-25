/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_ppc_fat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:38:06 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 16:56:16 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	swap_header_data(struct mach_header	*header)
{
	header->magic = swap_endian(header->magic);
	header->cputype = swap_endian(header->cputype);
	header->cpusubtype = swap_endian(header->cpusubtype);
	header->filetype = swap_endian(header->filetype);
	header->ncmds = swap_endian(header->ncmds);
	header->sizeofcmds = swap_endian(header->sizeofcmds);
	header->flags = swap_endian(header->flags);
}

void	print_off_ppc(t_vault *vault, unsigned long cpt)
{
	off_t			adr;
	struct section	*sect_hdr;

	sect_hdr = vault->sect_hdr;
	adr = sect_hdr->addr;
	ft_printf("%.8x%c", (swap_long_endian(adr) + cpt), '\t');
}

void	psdp_2(t_vault *vault, unsigned long cpt)
{
	if (cpt != 0 && (cpt % 16) == 0)
		ft_printf("\n");
	if ((cpt % 16) == 0)
		print_off_ppc(vault, cpt);
}

int		psdp_3(t_vault *vault, unsigned long cpt)
{
	char			*hex_letter;

	if ((hex_letter = offset_jumper(vault, vault->sect, cpt)) == NULL)
	{
		ft_printf("\n\033[31motool error :\n\ttruncated or malformed object ");
		ft_printf("(offset required past the end of the file).\033[0m\n");
		return (-1);
	}
	ft_printf("%0.2hhx", *hex_letter);
	return (0);
}

int		print_sect_dump_ppc(t_vault *vault)
{
	struct section	*s_hdr;
	unsigned long	cpt;
	unsigned long	i;

	cpt = 0;
	s_hdr = vault->sect_hdr;
	s_hdr->offset = swap_long_endian(s_hdr->offset);
	s_hdr->size = swap_long_endian(s_hdr->size);
	vault->sect = offset_jumper(vault, vault->o_dump, s_hdr->offset);
	ft_printf("Contents of (%s,%s) section\n", s_hdr->segname, s_hdr->sectname);
	while (cpt < s_hdr->size && vault->sect != NULL)
	{
		psdp_2(vault, cpt);
		i = 0;
		while (i < 4)
		{
			if (psdp_3(vault, cpt) == -1)
				return (-1);
			i++;
			cpt += sizeof(char);
		}
		ft_printf(" ");
	}
	ft_printf("\n");
	return (1);
}
