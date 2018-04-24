/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ppc_fat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:46:07 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:35:57 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_off_ppc(t_vault *vault, unsigned long cpt)
{
	off_t			adr;
	struct section	*sect_hdr;

	sect_hdr = vault->sect_hdr;
	adr = sect_hdr->addr;
	ft_printf("%.8x%c", (swap_long_endian(adr) + cpt), '\t');
}

int		print_sect_dump_ppc(t_vault *vault)
{
	struct section	*sect_hdr;
	unsigned long	cpt;
	unsigned long	i;
	char			*hex_letter;

	cpt = 0;
	hex_letter = NULL;
	sect_hdr = vault->sect_hdr;
	sect_hdr->offset = swap_long_endian(sect_hdr->offset);
	sect_hdr->size = swap_long_endian(sect_hdr->size);
	vault->sect = offset_jumper(vault, vault->o_dump, sect_hdr->offset);
	ft_printf("Contents of (%s,%s) section\n", sect_hdr->segname, sect_hdr->sectname);

	while (cpt < sect_hdr->size && vault->sect != NULL)
	{
		if (cpt != 0 && (cpt % 16) == 0)
			ft_printf("\n");
		if ((cpt % 16) == 0)
			print_off_ppc(vault, cpt);
		i = 0;
		while (i < 4)
		{
			if ((hex_letter = offset_jumper(vault, vault->sect, cpt)) == NULL)
			{
				ft_printf("\n\033[31motool error :\n\ttruncated or malformed object ");
				ft_printf("(offset required past the end of the file).\033[0m\n");
				return (-1);
			}
			ft_printf("%0.2hhx", *hex_letter);
			i++;
			cpt += sizeof(char);
		}
		ft_printf(" ");
	}
	ft_printf("\n");
	return (1);
}

int		check_seg_sect_name_ppc_fat(t_vault *vault, struct load_command *lc)
{
	struct section *sect;

	if ((sect = offset_jumper(vault, lc, sizeof(struct segment_command))) == NULL)
		return (-1);
	if (((ft_strncmp(sect->segname, "__TEXT", 6)) == 0) && \
	(ft_strncmp(sect->sectname, "__text", 6) == 0))
	{
		vault->sect_hdr = sect;
		return (1);
	}
	return (0);
}

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

int		get_text_text_sec_ppc_fat(t_vault *vault)
{
	unsigned int		i;
	struct mach_header	*header;
	struct load_command	*lc;
	int					ret;

	i = 0;
	header = vault->o_dump;
	lc = offset_jumper(vault, vault->o_dump, sizeof(*header));
	swap_header_data(header);
	while (i < header->ncmds && lc != NULL)
	{
		if ((ret = check_seg_sect_name_ppc_fat(vault, lc)) == -1)
			break;
		if (swap_endian(lc->cmd) == LC_SEGMENT && (ret == 1))
			return (1);
		if ((lc = offset_jumper(vault, lc, swap_endian(lc->cmdsize))) == NULL)
			return (-1);
		i++;
	}
	return (-1);
}

int		handle_ppc_fat(t_vault *vault, char *path)
{
	if (vault->o_dump == NULL)
	{
		vault->o_dump = vault->fat_dump;
		vault->fat_dump = NULL;
	}
	if (get_text_text_sec_ppc_fat(vault) == -1)
		return (-1);
	ft_printf("%s (architecture ppc):\n", path);
	print_sect_dump_ppc(vault);
	return (1);
}