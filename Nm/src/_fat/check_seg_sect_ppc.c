/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seg_sect_ppc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:11:47 by galy              #+#    #+#             */
/*   Updated: 2018/05/11 14:18:33 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char			handle_sect_name_to_letter_ppc(char *sectname, int upper)
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

unsigned int	gslppc(t_lc_lnk **tmp_seg, t_sect_lnk_32 **tmp_sect, \
unsigned int i, int sector)
{
	if (sector == 1)
	{
		*tmp_seg = (*tmp_seg)->next;
		*tmp_sect = (*tmp_seg)->sect_lst.lnk_32;
		return (0);
	}
	else if (sector == 2)
	{
		i = (*tmp_sect != NULL) ? (i + 1) : i;
		if ((*tmp_sect)->next != NULL)
			*tmp_sect = (*tmp_sect)->next;
		else
		{
			*tmp_seg = (*tmp_seg)->next;
			*tmp_sect = (*tmp_seg)->sect_lst.lnk_32;
		}
		return (i);
	}
	return (-1);
}

char			get_sect_letter_ppc(t_vault *vault, unsigned int n_sect, \
int upper)
{
	unsigned int		i;
	t_lc_lnk			*tmp_seg;
	t_sect_lnk_32		*tmp_sect;
	struct mach_header	*header;

	i = 1;
	tmp_seg = vault->lc_lst;
	tmp_sect = tmp_seg->sect_lst.lnk_32;
	header = vault->header;
	while (i < vault->nsyms && tmp_seg != NULL)
	{
		if (tmp_sect == NULL)
			gslppc(&tmp_seg, &tmp_sect, i, 1);
		else
		{
			if (i == n_sect && tmp_sect != NULL)
				break ;
			i = gslppc(&tmp_seg, &tmp_sect, i, 2);
		}
	}
	return (handle_sect_name_to_letter_ppc(tmp_sect->sect_32->sectname, upper));
}

char			handle_n_type_mask_ppc(t_vault *vault, unsigned int i, \
int upper)
{
	char	letter;

	letter = '@';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_ABS)
		letter = upper ? 'A' : 'a';
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_SECT)
		letter = get_sect_letter_ppc(vault, \
		vault->tab_sym_meta[i]->n_sect, upper);
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_INDR)
		letter = 'I';
	return (letter);
}

char			print_sym_sect_ppc(t_vault *vault, unsigned int i)
{
	int		ext;
	char	letter;
	int		num_type;

	ext = 0;
	letter = '*';
	num_type = vault->tab_sym_meta[i]->n_type;
	if ((num_type & N_STAB) != 0)
		return ('N');
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
