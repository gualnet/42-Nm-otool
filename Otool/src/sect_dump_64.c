/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect_dump_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:57:35 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 19:01:47 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_off(t_vault *vault, unsigned long cpt)
{
	off_t				adr;
	struct section_64	*sect_hdr;

	sect_hdr = vault->sect_hdr;
	adr = sect_hdr->addr;
	if ((vault->file_nfo & M_64B) == M_64B)
		ft_printf("%.16lx%c", adr + cpt, '\t');
	else
		ft_printf("%.16lx%c", adr + cpt, '\t');
}

int		err_msg_print_sect_dump_64(void)
{
	ft_printf("\n\033[31motool error :\n\ttruncated or malformed object "
	"(offset required past the end of the file).\033[0m\n");
	return (-1);
}

int		print_sect_dump_64(t_vault *vault)
{
	struct section_64	*sect_hdr;
	unsigned long		cpt;
	char				*hex_letter;

	cpt = 0;
	hex_letter = NULL;
	sect_hdr = vault->sect_hdr;
	if ((vault->sect = offset_jumper(vault, vault->o_dump, \
	sect_hdr->offset)) == NULL)
		return (-1);
	ft_printf("Contents of (%s,%s) section\n", \
	sect_hdr->segname, sect_hdr->sectname);
	while (cpt < sect_hdr->size && vault->sect != NULL)
	{
		if (cpt != 0 && (cpt % 16) == 0)
			ft_printf("\n");
		if ((cpt % 16) == 0)
			print_off(vault, cpt);
		if ((hex_letter = offset_jumper(vault, vault->sect, cpt)) == NULL)
			return (err_msg_print_sect_dump_64());
		ft_printf("%0.2hhx ", *hex_letter);
		cpt += sizeof(char);
	}
	ft_printf("\n");
	return (1);
}
