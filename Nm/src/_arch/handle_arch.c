/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:09:12 by galy              #+#    #+#             */
/*   Updated: 2018/03/30 22:56:40 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_offset(t_vault *vault, void *ptr)
{
	void	*start;
	if (vault->ar_dump != NULL)
	{
		start = (void*)vault->ar_dump;
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
	// ft_printf("\nCALL FREE_USELESS_VAULT_COMP\n");
	delete_all_lst(vault);

	vault->f_dump = NULL;
	
	// ft_printf("END FREE_USELESS_VAULT_COMP\n");
}

void	offset_init(t_vault *vault, t_arch_info *arch)
{
	long	jump;

	jump = 0;
	vault->ar_dump = vault->f_dump;
	vault->f_dump = NULL;
	arch->off_symtab_hdr = offset_jumper(vault, (void*)vault->ar_dump, SARMAG);
	jump = sizeof(*arch->off_symtab_hdr) + LONG_NAME_SIZE;
	arch->off_symbol_tab = offset_jumper(vault, (void*)arch->off_symtab_hdr, jump);
}

// int		compare_object_name(int old_offset, int new_offset)
// {
	
// }

int		check_double_occur(t_vault *vault, t_arch_info *arch, int tabsym_off, unsigned int max_offset)
{
	unsigned int	cur_offset;
	void			*symtab;
	
	cur_offset = arch->off_symbol_tab - vault->ar_dump + 4;
	while (cur_offset < max_offset)
	{
		// symtab = (void*)vault->ar_dump + cur_offset;
		symtab = offset_jumper(vault, vault->ar_dump, cur_offset);
		if (tabsym_off == *(int*)(symtab + 4))
			return (-1);
		cur_offset += (sizeof(void*));
	}
	return (1);
}

void	get_nbr_symbols(t_vault *vault, t_arch_info *arch)
{
	unsigned int	counter;
	unsigned int	symtab_size;
	unsigned int	max_offset;
	unsigned int	cur_offset;
	void			*symtab = NULL;

	counter = 0;
	symtab_size = *(size_t*)arch->off_symbol_tab;
	max_offset = arch->off_symbol_tab - vault->ar_dump + symtab_size + 4; //offset_jump_neg
	cur_offset = arch->off_symbol_tab - vault->ar_dump + 4; //offset_jump_neg
	arch->off_symstr_tab = offset_jumper(vault, (void*)arch->off_symbol_tab, symtab_size);

	// symtab = (void*)vault->ar_dump + cur_offset;
	// void	*strtab = symtab + symtab_size; // pour le print
	while (cur_offset < max_offset)
	{
		symtab = offset_jumper(vault, vault->ar_dump, cur_offset);
		// ft_printf("offset count [%x/%x]-", cur_offset, max_offset);
		// ft_printf("[%x]-", *(int*)symtab);
		// ft_printf("[%s]-->", strtab + *(int*)symtab + 4);
		// ft_printf("[%x]-", *(int*)(symtab + 4));
		// ft_printf("\n");
		if (check_double_occur(vault, arch, *(int*)(symtab + 4), cur_offset) == 1)
		{
			counter++;
		}
		cur_offset += (sizeof(void*));
		// ft_printf("counter[%d]\n", counter);
	}
	arch->nbr_obj = counter;
}

void	print_object_path(t_vault *vault, struct ar_hdr *obj_hdr, char *path, char hdr_ext)
{
	char *o_name;

	if (hdr_ext == 1)
	{
		// o_name = (void*)obj_hdr + sizeof(struct ar_hdr);
		o_name = offset_jumper(vault, obj_hdr, sizeof(struct ar_hdr));
		ft_printf("%s", path);
		ft_printf("(");
		read_undelimited_str(o_name, LONG_NAME_SIZE);
		ft_printf("):\n");
	}
	else
	{
		o_name = (void*)obj_hdr->ar_name;
		ft_printf("%s", path);
		ft_printf("(");
		read_undelimited_str(o_name, AR_NAME_SIZE);
		ft_printf("):\n");
	}
	
}

void	jump_obj_hdr(t_vault *vault, t_arch_info *arch, char *path)
{
	// ft_printf("\nCALL JUMP_OBJ_HDR\n");
	struct ar_hdr	*obj_hdr;
	unsigned int	i;
	char			hdr_ext;
	long			jump;
	
	jump = sizeof(*arch->off_symtab_hdr) + ft_atoi(arch->off_symtab_hdr->ar_size);
	obj_hdr = offset_jumper(vault, arch->off_symtab_hdr, jump);
	
	
	if (ft_strncmp(obj_hdr->ar_name, AR_EFMT1, 2) == 0)
	{
		jump = sizeof(*obj_hdr) + LONG_NAME_SIZE;
		vault->f_dump = offset_jumper(vault, (void*)obj_hdr, jump);
		hdr_ext = 1;
	}
	else
	{
		jump = sizeof(*obj_hdr);
		vault->f_dump = offset_jumper(vault, (void*)obj_hdr, jump);
		hdr_ext = 0;
	}
	
	vault->header = vault->f_dump;
	// print_offset(vault, (void*)obj_hdr);
	inter_cmds(vault);
	print_object_path(vault, obj_hdr, path, hdr_ext);
	display_list(vault);
	free_useless_vault_components(vault);
	
	i = 1;
	while (i < arch->nbr_obj)
	{
		// obj_hdr = (void*)obj_hdr + sizeof(*obj_hdr) + ft_atoi(obj_hdr->ar_size);
		jump = sizeof(*obj_hdr) + ft_atoi(obj_hdr->ar_size);
		obj_hdr = offset_jumper(vault, obj_hdr, jump);

		if (ft_strncmp(obj_hdr->ar_name, AR_EFMT1, 2) == 0)
		{
			// vault->f_dump = (void*)obj_hdr + sizeof(*obj_hdr) + LONG_NAME_SIZE;
			jump = sizeof(*obj_hdr) + LONG_NAME_SIZE;
			vault->f_dump = offset_jumper(vault, obj_hdr, jump);
			hdr_ext = 1;
		}
		else
		{
			// vault->f_dump = (void*)obj_hdr + sizeof(*obj_hdr);
			vault->f_dump = offset_jumper(vault, obj_hdr, sizeof(*obj_hdr));
			hdr_ext = 0;
		}
		vault->header = (void*)vault->f_dump - 8; //jump neg
		inter_cmds(vault);
		// print_offset(vault, (void*)obj_hdr);
		print_object_path(vault, obj_hdr, path, hdr_ext);
		display_list(vault);
		if (i < arch->nbr_obj - 1)
			ft_printf("\n");
		free_useless_vault_components(vault);
		i++;
	}
	
	
}

void	handle_arch(t_vault *vault, char *path)
{
	// ft_printf("\nCALL HANDLE_ARCH\n");
	t_arch_info	*arch_info;
	arch_info = malloc(sizeof(struct s_arch_info));

	offset_init(vault, arch_info);

	//get number of symbols in symbol tab
	get_nbr_symbols(vault, arch_info);
	// ft_printf("\narch_info->nbr_obj %d\n", arch_info->nbr_obj);

	//jump between objects
	jump_obj_hdr(vault, arch_info, path);
}