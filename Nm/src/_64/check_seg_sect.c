/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seg_sect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:08:45 by galy              #+#    #+#             */
/*   Updated: 2018/05/11 13:44:18 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char			handle_sect_name_to_letter(char *sectname, int upper)
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

unsigned int	gsl_2(t_lc_lnk **tmp_seg, t_sect_lnk **tmp_sect, \
unsigned int i, int sector)
{
	if (sector == 1)
	{
		(*tmp_seg) = (*tmp_seg)->next;
		(*tmp_sect) = (*tmp_seg)->sect_lst.lnk_64;
		return (0);
	}
	if (sector == 2)
	{
		i = (tmp_sect != NULL) ? (i + 1) : i;
		if ((*tmp_sect)->next != NULL)
			(*tmp_sect) = (*tmp_sect)->next;
		else if ((*tmp_seg)->next != NULL)
		{
			(*tmp_seg) = (*tmp_seg)->next;
			(*tmp_sect) = (*tmp_seg)->sect_lst.lnk_64;
		}
		return (i);
	}
	return (-1);
}

char			get_sect_letter(t_vault *vault, unsigned int n_sect, int upper)
{
	unsigned int			i;
	t_lc_lnk				*tmp_seg;
	t_sect_lnk				*tmp_sect;
	struct mach_header_64	*header;

	i = 1;
	tmp_seg = vault->lc_lst;
	tmp_sect = tmp_seg->sect_lst.lnk_64;
	header = vault->header;
	while (i < vault->nbr_sect && tmp_seg)
	{
		if (tmp_sect == NULL)
			gsl_2(&tmp_seg, &tmp_sect, i, 1);
		else
		{
			if (i == n_sect && tmp_sect != NULL)
				break ;
			i = gsl_2(&tmp_seg, &tmp_sect, i, 2);
		}
	}
	return (handle_sect_name_to_letter(tmp_sect->sect->sectname, upper));
}

char			handle_n_type_mask(t_vault *vault, unsigned int i, int upper)
{
	char letter;

	letter = '@';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_ABS)
		letter = upper ? 'A' : 'a';
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_SECT)
		letter = get_sect_letter(vault, vault->tab_sym_meta[i]->n_sect, upper);
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_INDR)
		letter = 'I';
	return (letter);
}

char			print_sym_sect(t_vault *vault, unsigned int i)
{
	int		ext;
	char	letter;

	ext = 0;
	letter = '*';
	if ((vault->tab_sym_meta[i]->n_type & N_STAB) != 0)
		return ('N');
	if ((vault->tab_sym_meta[i]->n_type & N_PEXT) != 0)
		ext = 0;
	if ((vault->tab_sym_meta[i]->n_type & N_EXT) != 0)
		ext = 1;
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_UNDF)
		letter = ext ? 'U' : 'u';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) != 0)
		letter = handle_n_type_mask(vault, i, ext);
	return (letter);
}
