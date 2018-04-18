/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seg_sect_ppc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:11:47 by galy              #+#    #+#             */
/*   Updated: 2018/04/18 11:34:57 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	handle_sect_name_to_letter_ppc(char *sectname, int upper)
{
	if (ft_strcmp(sectname, "__text") == 0)
		return (upper ? 'T' : 't');
	if (ft_strcmp(sectname, "__bss") == 0)
		return (upper ? 'B' : 'b');
	if (ft_strcmp(sectname, "__data") == 0)
		return (upper ? 'D' : 'd');
	if (ft_strcmp(sectname, "__common") == 0)
		return (upper ? 'S' : 's');
	if (ft_strcmp(sectname, "__const") == 0)
		return (upper ? 'S' : 's');
	return (upper ? 'S' : 's');
}

char	get_sect_letter_ppc(t_vault *vault, unsigned int n_sect, int upper)
{
	unsigned int		i;
	t_lc_lnk			*tmp_seg;
	t_sect_lnk_32		*tmp_sect;
	struct mach_header	*header;

	i = 1;
	tmp_seg = vault->lc_lst;
	tmp_sect = tmp_seg->sect_lst.lnk_32;
	header = vault->header;
	while (i < swap_endian(header->ncmds) && tmp_seg != NULL)
	{
		if (tmp_sect == NULL)
		{
			tmp_seg = tmp_seg->next;
			tmp_sect = tmp_seg->sect_lst.lnk_32;
		}
		else
		{
			if (i == n_sect && tmp_sect != NULL)
				break;
			i = (tmp_sect != NULL) ? (i + 1) : i;
			if (tmp_sect->next != NULL)
				tmp_sect = tmp_sect->next;
			else
			{
				tmp_seg = tmp_seg->next;
				tmp_sect = tmp_seg->sect_lst.lnk_32;
			}
		}
	}
	return (handle_sect_name_to_letter_ppc(tmp_sect->sect_32->sectname, upper));
}

char	handle_n_type_mask_ppc(t_vault *vault, unsigned int i, int upper)
{
	char	letter;
	
	letter = '@';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_ABS)
		letter = upper ? 'A' : 'a';
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_SECT)
	{
		letter = get_sect_letter_ppc(vault, vault->tab_sym_meta[i]->n_sect, upper);
	}
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_INDR)
		letter = 'I';
	// else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_PBUD)
	// {
	// 	// ft_printf("prebound undefined ");
	// }
	return (letter);
}

char	print_sym_sect_ppc(t_vault *vault, unsigned int i)
{
	int		ext;
	char	letter;
	int		num_type;

	ext = 0;
	letter = '*';
	// num_type = swap_endian(vault->tab_sym_meta[i]->n_type);
	num_type = vault->tab_sym_meta[i]->n_type;
	if ((num_type & N_STAB) != 0)
		letter = 'N';
	if ((num_type & N_PEXT) != 0)
		ext = 0;
	if ((num_type & N_EXT) != 0)
		ext = 1;
	if ((num_type & N_TYPE) == N_UNDF)
		letter = ext ? 'U' : 'u';
	if ((num_type & N_TYPE) != 0)
		letter = handle_n_type_mask_ppc(vault, i, ext);
	return (letter);
}