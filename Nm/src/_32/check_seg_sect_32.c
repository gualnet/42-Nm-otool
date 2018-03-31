/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seg_sect_32.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 05:28:34 by galy              #+#    #+#             */
/*   Updated: 2018/03/31 06:40:43 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	handle_sect_name_to_letter_32(char *sectname, int upper)
{
	if (ft_strcmp(sectname, "__text") == 0)
		return (upper ? 'T' : 't');
	if (ft_strcmp(sectname, "__bss") == 0)
		return (upper ? 'B' : 'b');
	if (ft_strcmp(sectname, "__data") == 0)
		return (upper ? 'B' : 'b');
	return ('^');
}

char	get_sect_letter_32(t_vault *vault, unsigned int n_sect, int upper)
{
	unsigned int		i;
	t_lc_lnk			*tmp_seg;
	t_sect_lnk			*tmp_sect;
	struct mach_header	*header;

	i = 1;
	tmp_seg = vault->lc_lst;
	tmp_sect = tmp_seg->sect_lst;
	header = vault->header;
	while (i < header->ncmds && tmp_seg != NULL)
	{
		if (tmp_sect == NULL)
		{
			tmp_seg = tmp_seg->next;
			tmp_sect = tmp_seg->sect_lst;
		}
		else
		{
			// tmp_sect = tmp_seg->sect_lst;
			ft_printf("%d - inter sectname [%s]\n", i, tmp_sect->sect_32->sectname);
			if (i == n_sect && tmp_sect != NULL)
				break;
			i = (tmp_sect != NULL) ? (i + 1) : i;
			if (tmp_sect->next != NULL)
				tmp_sect = tmp_sect->next;
			else
				tmp_seg = tmp_seg->next;
		}
	}
	return (handle_sect_name_to_letter_32(tmp_sect->sect->sectname, upper));
}

char	handle_n_type_mask_32(t_vault *vault, unsigned int i, int upper)
{
	char	letter;
	
	letter = '@';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_ABS)
		letter = upper ? 'A' : 'a';
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_SECT)
	{
		print_offset(vault->f_dump, vault->tab_sym_meta[i]);
		letter = get_sect_letter_32(vault, vault->tab_sym_meta[i]->n_sect, upper);
	}
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_INDR)
		letter = 'I';
	// else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_PBUD)
	// {
	// 	// ft_printf("prebound undefined ");
	// }
	return (letter);
}

char	print_sym_sect_32(t_vault *vault, unsigned int i)
{
	int		ext;
	char	letter;	

	ext = 0;
	letter = '*';
	if ((vault->tab_sym_meta[i]->n_type & N_STAB) != 0)
		letter = 'N';
	if ((vault->tab_sym_meta[i]->n_type & N_PEXT) != 0)
		ext = 1;
	if ((vault->tab_sym_meta[i]->n_type & N_EXT) != 0)
		ext = 1;
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_UNDF)
		letter = ext ? 'U' : 'u';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) != 0)
		letter = handle_n_type_mask_32(vault, i, ext);
	return (letter);
}