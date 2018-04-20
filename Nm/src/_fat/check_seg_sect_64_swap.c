/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seg_sect_64_swap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:08:45 by galy              #+#    #+#             */
/*   Updated: 2018/04/20 12:31:51 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	handle_sect_name_to_letter_64_swap(char *sectname, int upper)
{
	char name[16];

	ft_bzero(&name, 16);
	ft_memcpy(&name, sectname, 16);
	if (ft_strcmp((const char*)&name, "__text") == 0)
		return (upper ? 'T' : 't');
	if (ft_strcmp((const char*)&name, "__bss") == 0)
		return (upper ? 'B' : 'b');
	if (ft_strcmp((const char*)&name, "__data") == 0)
		return (upper ? 'D' : 'd');
	if (ft_strcmp((const char*)&name, "__common") == 0)
		return (upper ? 'S' : 's');
	if (ft_strcmp((const char*)&name, "__const") == 0)
		return (upper ? 'S' : 's');
	return (upper ? 'S' : 's');
}

char	get_sect_letter_64_swap(t_vault *vault, unsigned int n_sect, int upper)
{
	unsigned int			i;
	t_lc_lnk				*tmp_seg;
	t_sect_lnk				*tmp_sect;
	struct mach_header_64	*header;
	unsigned int			tot_sect;

	i = 1;
	tmp_seg = vault->lc_lst;
	tot_sect = swap_endian(((struct segment_command_64*)(tmp_seg))->nsects);
	tmp_sect = tmp_seg->sect_lst.lnk_64;
	header = vault->header;
	while (i < tot_sect && tmp_seg)
	{
		if (tmp_sect == NULL)
		{
			tmp_seg = tmp_seg->next;
			tmp_sect = tmp_seg->sect_lst.lnk_64;
		}
		else
		{
			if (i == n_sect && tmp_sect != NULL)
				break;
			i = (tmp_sect != NULL) ? (i + 1) : i;
			if (tmp_sect->next != NULL)
				tmp_sect = tmp_sect->next;
			else if (tmp_seg->next != NULL)
			{
				tmp_seg = tmp_seg->next;
				tmp_sect = tmp_seg->sect_lst.lnk_64;
			}
		}
		
	}
	return (handle_sect_name_to_letter_64_swap(tmp_sect->sect->sectname, upper));
}

char	handle_n_type_mask_64_swap(t_vault *vault, unsigned int i, int upper)
{
	char letter;
	
	letter = '@';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_ABS)
		letter = upper ? 'A' : 'a';
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_SECT)
		letter = get_sect_letter_64_swap(vault, vault->tab_sym_meta[i]->n_sect, upper);
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_INDR)
		letter = 'I';
	return (letter);
}

char	print_sym_sect_64_swap(t_vault *vault, unsigned int i)
{
	int ext;
	char letter;	

	ext = 0;
	letter = '*';

	if ((vault->tab_sym_meta[i]->n_type & N_STAB) != 0)
		return (letter = 'N');
	if ((vault->tab_sym_meta[i]->n_type & N_PEXT) != 0)
		ext = 0;
	if ((vault->tab_sym_meta[i]->n_type & N_EXT) != 0)
		ext = 1;
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_UNDF)
		letter = ext ? 'U' : 'u';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) != 0)
		letter = handle_n_type_mask_64_swap(vault, i, ext);
	return (letter);
}