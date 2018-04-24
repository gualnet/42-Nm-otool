/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 16:05:03 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 17:14:49 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		check_double_occur(t_vault *vault, t_arch_info *arch_i, int tabsym_off, unsigned int max_offset)
{
	unsigned int	cur_offset;
	void 			*symtab;
	
	cur_offset = arch_i->off_symbol_tab - vault->ar_dump + 8;
	while (cur_offset < max_offset)
	{
		if ((symtab = offset_jumper(vault, vault->ar_dump, cur_offset)) == NULL)
			return (-1);
		if (tabsym_off == *(int*)symtab)
			return (-1);
		cur_offset += 2 * sizeof(int);
	}
	return (1);
}

int		get_nbr_symbols(t_vault *vault, t_arch_info *arch_i)
{
	unsigned int	counter;
	unsigned int	max_offset;
	unsigned int	cur_offset;
	void			*symtab;
	
	counter = 0;
	max_offset = arch_i->off_symbol_tab - \
	vault->ar_dump + *(int*)arch_i->off_symbol_tab + 4;
	cur_offset = arch_i->off_symbol_tab - vault->ar_dump + 8;
	while (cur_offset < max_offset)
	{
		if ((symtab = offset_jumper(vault, vault->ar_dump, cur_offset)) == NULL)
			return (-1);
		if (check_double_occur(vault, arch_i, *(int*)symtab, cur_offset) == 1)
			counter++;
		cur_offset += 2 * sizeof(int);
	}
	arch_i->nbr_obj = counter;
	return (1);
}

int		set_arch_i(t_vault *vault, t_arch_info *arch_i)
{
	long	jump;

	jump = 0;
	arch_i->symtab_hdr = (void*)vault->ar_dump + SARMAG;
	//
	jump = sizeof(struct ar_hdr); 
	jump += (ft_strncmp(arch_i->symtab_hdr->ar_name, AR_EFMT1, 2) == 0) ? 20 : 0;
	arch_i->off_symbol_tab = offset_jumper(vault, arch_i->symtab_hdr, jump);
	//
	jump = *(int*)arch_i->off_symbol_tab + sizeof(int);
	arch_i->off_symstr_tab = offset_jumper(vault, arch_i->off_symbol_tab, jump);
	//
	// print_offset(vault, arch_i->symtab_hdr);
	// print_offset(vault, arch_i->off_symbol_tab);
	// print_offset(vault, arch_i->off_symstr_tab);
	if (arch_i->symtab_hdr == NULL || arch_i->off_symbol_tab == NULL || arch_i->off_symstr_tab == NULL)
		return (-1);
	return (1);
}

int		handle_arch(t_vault *vault, char *path)
{
	t_arch_info	arch_i;
	
	if (vault->ar_dump == NULL)
	{
		vault->ar_dump = vault->fat_dump;
		vault->fat_dump = NULL;
	}

	if (set_arch_i(vault, &arch_i) == -1)
		return (-1);
	
	if (get_nbr_symbols(vault, &arch_i) == - 1)
		return (-1);

	if (jump_obj_hdr(vault, &arch_i, path) == -1)
		return (-1);
	return (0);
}