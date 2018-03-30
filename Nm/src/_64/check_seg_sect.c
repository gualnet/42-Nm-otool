/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seg_sect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:08:45 by galy              #+#    #+#             */
/*   Updated: 2018/03/30 16:51:43 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	handle_sect_name_to_letter(char *sectname, int upper)
{
	// ft_printf("==sect [%s]\n", sectname);
	if (ft_strcmp(sectname, "__text") == 0)
	{
		return (upper ? 'T' : 't');
	}
	if (ft_strcmp(sectname, "__bss") == 0)
	{
		return (upper ? 'B' : 'b');
	}
	return ('^');
}

char	get_sect_letter(t_vault *vault, unsigned int n_sect, int upper)
{
	unsigned int	i;
	t_lc_lnk		*tmp_seg;
	t_sect_lnk		*tmp_sect;
	struct mach_header_64	*header;

	i = 1;
	tmp_seg = vault->lc_lst;
	tmp_sect = tmp_seg->sect_lst;
	header = vault->header;
	// ft_printf("tmp_seg[%p]\n", tmp_seg);
	while (i < header->ncmds && tmp_seg != NULL)
	{
		// ft_printf("i[%d] - header->ncmds[%d]\n", i, header->ncmds);
		// ft_printf("vault->lc_lst->sect->segname[%p]\n", vault->lc_lst->sect_lst->sect->segname);
		
		// tmp_sect = tmp_seg->sect_lst;
		// ft_printf("tmp_sect[%p]\n", tmp_sect);
		if (i == n_sect && tmp_sect != NULL)
		{
			// ft_printf("\tbreak @ %d\n", i);
			break;
		}
		// ft_printf("----------------i[%d]->sectname[%s]\n", i, tmp_sect->sect->sectname);
		i = (tmp_sect != NULL) ? (i + 1) : i;
		if (tmp_sect->next != NULL)
			tmp_sect = tmp_sect->next;
		else
			tmp_seg = tmp_seg->next;
		// ft_printf("----------------i[%d]->sectname[%s]\n", i, tmp_sect->sect->sectname);
	}
	// ft_printf("[%d]tmp [%s]\n", i, tmp_sect->sect->segname);
	// ft_printf("[%d]tmp [%s]\n", i, tmp_sect->sect->sectname);
	return (handle_sect_name_to_letter(tmp_sect->sect->sectname, upper));
	exit (0);
}

char	handle_n_type_mask(t_vault *vault, unsigned int i, int upper)
{
	char letter;
	
	letter = '@';
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_ABS)
		letter = upper ? 'A' : 'a';
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_SECT)
		letter = get_sect_letter(vault, vault->tab_sym_meta[i]->n_sect, upper);
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_PBUD)
		ft_printf("prebound undefined ");
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_INDR)
		letter = 'I';
	return (letter);
}

char	print_sym_sect(t_vault *vault, unsigned int i)
{
	int ext;
	char letter;	

	ext = 0;
	letter = '*';
	// ft_printf("---[%b]---", vault->tab_sym_meta[i]->n_type);
	if ((vault->tab_sym_meta[i]->n_type & N_STAB) != 0)
		letter = 'N';
	if ((vault->tab_sym_meta[i]->n_type & N_PEXT) != 0)
	{
		// ft_printf("private external symbol ");
		ext = 1;
	}
	if ((vault->tab_sym_meta[i]->n_type & N_EXT) != 0)
	{
		// ft_printf("external symbol ");
		ext = 1;
	}
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_UNDF)
		letter = ext ? 'U' : 'u';
	// // ft_printf("ext = %d\n", ext);
	if ((vault->tab_sym_meta[i]->n_type & N_TYPE) != 0)
		letter = handle_n_type_mask(vault, i, ext);
	return (letter);
	// ft_printf("%c ", letter); //sortie
}