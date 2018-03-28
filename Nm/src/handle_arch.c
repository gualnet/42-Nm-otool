/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:09:12 by galy              #+#    #+#             */
/*   Updated: 2018/03/28 20:19:19 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_offset(t_vault *vault, void *ptr)
{
	void	*start;
	if (vault->ar_dump != NULL)
	{
		start = (void*)vault->ar_dump;
		ft_printf("-->001");
	}
	else
		start = (void*)vault->f_dump;

	// ft_printf("1-start[%p]\n", start);
	// ft_printf("2-ptr[%p]\n", ptr);
	// ft_printf("3-ptr - start[%p]\n", ptr - start);
	ft_printf("\n\033[36moffset[%x]\033[00m\n", ptr - start,ptr - start);
}

void	free_useless_vault_components(t_vault *vault)
{
	ft_printf("\nCALL FREE_USELESS_VAULT_COMP\n");
	delete_all_lst(vault);

	vault->f_dump = NULL;
	
	ft_printf("END FREE_USELESS_VAULT_COMP\n");
}

void	offset_init(t_vault *vault, t_arch_info *arch)
{
	vault->ar_dump = vault->f_dump;
	vault->f_dump = NULL;

	arch->off_symtab_hdr = (void*)vault->ar_dump + SARMAG;
	arch->off_symbol_tab = (void*)arch->off_symtab_hdr + sizeof(*arch->off_symtab_hdr) + LONG_NAME_SIZE;
}

void	get_nbr_symbols(t_vault *vault, t_arch_info *arch)
{
	unsigned int	counter;
	unsigned int	symtab_size;
	unsigned int	max_offset;
	unsigned int	cur_offset;

	counter = 0;
	symtab_size = *(size_t*)arch->off_symbol_tab;
	max_offset = arch->off_symbol_tab - vault->ar_dump + symtab_size + 4;
	cur_offset = arch->off_symbol_tab - vault->ar_dump + 4;
	arch->off_symstr_tab = (void*)arch->off_symbol_tab + symtab_size;

	// void	*symtab = (void*)vault->ar_dump + cur_offset; // pour le print
	// void	*strtab = symtab + symtab_size; // pour le print
	while (cur_offset < max_offset)
	{
		// symtab = (void*)vault->ar_dump + cur_offset;
		// ft_printf("offset count [%x/%x]-", cur_offset, max_offset);
		// ft_printf("[%x]-", *(int*)symtab);
		// ft_printf("[%s]\n", strtab + *(int*)symtab + 4);
		counter++;
		cur_offset += (sizeof(void*));
	}
	arch->nbr_obj = counter;
}

void	jump_obj_hdr(t_vault *vault, t_arch_info *arch)
{
	ft_printf("\nCALL JUMP_OBJ_HDR\n");
	struct ar_hdr	*obj_hdr;
	
	obj_hdr = (void*)arch->off_symbol_tab + ft_atoi(arch->off_symtab_hdr->ar_size) - LONG_NAME_SIZE;
	
	vault->f_dump = (void*)obj_hdr + sizeof(*obj_hdr) + LONG_NAME_SIZE;
	vault->header = vault->f_dump;
	inter_cmds(vault);
	display_list(vault);
	free_useless_vault_components(vault);

	print_offset(vault, obj_hdr);
	obj_hdr = NULL;
	

	print_offset(vault, obj_hdr);
}

void	handle_arch(t_vault *vault)
{
	ft_printf("\nCALL HANDLE_ARCH\n");
	t_arch_info	*arch_info;
	arch_info = malloc(sizeof(struct s_arch_info));

	offset_init(vault, arch_info);

	//get number of symbols in symbol tab
	get_nbr_symbols(vault, arch_info);
	// ft_printf("\narch_info->nbr_obj %d\n", arch_info->nbr_obj);

	//jump between objects
	jump_obj_hdr(vault, arch_info);
}