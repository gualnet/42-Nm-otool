/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ppc_fat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:46:07 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 16:56:55 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		check_seg_sect_name_ppc_fat(t_vault *vault, struct load_command *lc)
{
	struct section *sect;

	if ((sect = offset_jumper(vault, lc, \
	sizeof(struct segment_command))) == NULL)
		return (-1);
	if (((ft_strncmp(sect->segname, "__TEXT", 6)) == 0) && \
	(ft_strncmp(sect->sectname, "__text", 6) == 0))
	{
		vault->sect_hdr = sect;
		return (1);
	}
	return (0);
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
			break ;
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
