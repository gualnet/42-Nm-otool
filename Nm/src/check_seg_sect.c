/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seg_sect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:08:45 by galy              #+#    #+#             */
/*   Updated: 2018/03/20 19:14:44 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	handle_sect_name_to_letter(char *sectname, int upper)
{
	if (ft_strcmp(sectname, "__text") == 0)
		return (upper ? 'T' : 't');
	return '^';
}

char	get_sect_letter(t_vault *vault, unsigned int n_sect, int upper)
{
	// ft_printf("coucou\n");
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
		
		tmp_sect = tmp_seg->sect_lst;
		// ft_printf("tmp_sect[%p]\n", tmp_sect);
		if (i == n_sect && tmp_sect != NULL)
		{
			// ft_printf("\tbreak @ %d\n", i);
			break;
		}
		i = (tmp_sect != NULL) ? (i + 1) : i;
		tmp_seg = (tmp_sect == NULL) ? tmp_seg->next : tmp_seg;
	}
	// ft_printf("[%d]tmp [%s]\n", i, tmp->sect->segname);
	// ft_printf("[%d]tmp [%s]\n", i, tmp->sect->sectname);
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

// #define	N_UNDF	0x0		/* undefined, n_sect == NO_SECT */
// #define	N_ABS	0x2		/* absolute, n_sect == NO_SECT */
// #define	N_SECT	0xe		/* defined in section number n_sect */
// #define	N_PBUD	0xc		/* prebound undefined (defined in a dylib) */
// #define N_INDR	0xa		/* indirect */