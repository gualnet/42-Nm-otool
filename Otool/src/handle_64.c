/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:26:41 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 12:03:36 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		check_seg_sect_name(t_vault *vault, struct load_command *lc)
{
	struct section_64 *sect;
	
	sect = offset_jumper(vault, lc, sizeof(struct segment_command_64));
	if (sect == NULL)
		return (-1);
	// ft_printf("[%s|%s]\n",sect->segname,sect->sectname);
	// void *truc = vault->o_dump;
	// vault->o_dump = NULL;
	// print_offset(vault, sect);
	// vault->o_dump = truc;
	if (((ft_strncmp(sect->segname, "__TEXT", 6)) == 0) && \
	(ft_strncmp(sect->sectname, "__text", 6) == 0))
	{
		vault->sect_hdr = sect;
		return (1);
	}
	return (0);
}

int		get_text_text_sec(t_vault *vault)
{
	// ft_printf("Call get_text_text_sec \n\n");
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						ret;

	i = 0;
	header = vault->o_dump;
	lc = offset_jumper(vault, vault->o_dump, sizeof(*header));
	while (i < header->ncmds && lc != NULL)
	{
		if ((ret = check_seg_sect_name(vault, lc)) == -1)
			break;
		if (lc->cmd == LC_SEGMENT_64 && (ret == 1))
			return (1);
		if ((lc = offset_jumper(vault, lc, lc->cmdsize)) == NULL)
			return (-1);
		i++;
	}
	return (-1);
}

int		handle_64(t_vault *vault)
{
	// ft_printf("Call handle_64 %p\n\n", vault);
	if (vault->o_dump == NULL)
	{
		vault->o_dump = vault->fat_dump;
		vault->fat_dump = NULL;
	}
	if (get_text_text_sec(vault) == -1)
		return (-1);
	print_sect_dump_64(vault);
	return (1);
}