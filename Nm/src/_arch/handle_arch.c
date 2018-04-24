/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:09:12 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:29:30 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_offset(t_vault *vault, void *ptr)
{
	void	*start;
	if (vault->ar_dump != NULL)
		start = (void*)vault->ar_dump;
	else
		start = (void*)vault->f_dump;
	ft_printf("\n\033[36moffset[%x]\033[00m\n", ptr - start,ptr - start);
}

void	free_useless_vault_components(t_vault *vault)
{
	delete_all_lst(vault);
	vault->f_dump = NULL;
	vault->header = NULL;
	vault->strtab = NULL;
}

int		offset_init(t_vault *vault, t_arch_info *arch)
{
	long	jump;

	jump = 0;
	vault->ar_dump = vault->f_dump;
	vault->f_dump = NULL;
	arch->off_symtab_hdr = offset_jumper(vault, (void*)vault->ar_dump, SARMAG);
	jump = sizeof(*arch->off_symtab_hdr) + ft_atoi(&arch->off_symtab_hdr->ar_name[3]);
	arch->off_symbol_tab = offset_jumper(vault, (void*)arch->off_symtab_hdr, jump);
	if (arch->off_symtab_hdr == NULL || arch->off_symbol_tab == NULL)
		return (-1);
	return (1);
}

int		check_double_occur(t_vault *vault, t_arch_info *arch, int tabsym_off, unsigned int max_offset)
{
	unsigned int	cur_offset;
	void			*symtab;
	
	cur_offset = arch->off_symbol_tab - vault->ar_dump + 4;
	while (cur_offset < max_offset)
	{
		symtab = offset_jumper(vault, vault->ar_dump, cur_offset);
		if (tabsym_off == *(int*)(symtab + 4) || symtab == NULL)
			return (-1);
		cur_offset += (sizeof(void*));
	}
	return (1);
}

int		get_nbr_symbols(t_vault *vault, t_arch_info *arch)
{
	unsigned int	counter;
	unsigned int	symtab_size;
	unsigned int	max_offset;
	unsigned int	cur_offset;
	void			*symtab;

	counter = 0;
	symtab_size = *(size_t*)arch->off_symbol_tab;
	max_offset = arch->off_symbol_tab - vault->ar_dump + symtab_size + 4;
	cur_offset = arch->off_symbol_tab - vault->ar_dump + 4;
	if ((arch->off_symstr_tab = offset_jumper(vault, \
	(void*)arch->off_symbol_tab, symtab_size + 4)) == NULL)
		return (-1);
	while (cur_offset < max_offset)
	{
		if ((symtab = offset_jumper(vault, vault->ar_dump, cur_offset)) == NULL)
			return (-1);
		if (check_double_occur(vault, arch, *(int*)(symtab + 4), cur_offset) == 1)
			counter++;
		cur_offset += (sizeof(void*));
	}
	arch->nbr_obj = counter;
	return (1);
}

void	print_object_path(t_vault *vault, struct ar_hdr *obj_hdr, char *path, char hdr_ext)
{
	char *o_name;

	if (hdr_ext == 1)
	{
		o_name = offset_jumper(vault, obj_hdr, sizeof(struct ar_hdr));
		ft_printf("\n%s", path);
		ft_printf("(");
		read_undelimited_str(o_name, ft_atoi(&obj_hdr->ar_name[3]));
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

int		jump_obj_hdr(t_vault *vault, t_arch_info *arch, char *path)
{
	struct ar_hdr	*obj_hdr;
	unsigned int	i;
	char			hdr_ext;
	long			jump;
	
	jump = sizeof(*arch->off_symtab_hdr) + ft_atoi(arch->off_symtab_hdr->ar_size);
	if ((obj_hdr = offset_jumper(vault, arch->off_symtab_hdr, jump)) == NULL)
		return (-1);
	if (ft_strncmp(obj_hdr->ar_name, AR_EFMT1, 2) == 0)
	{
		jump = sizeof(*obj_hdr) + ft_atoi(&obj_hdr->ar_name[3]);
		if ((vault->f_dump = offset_jumper(vault, (void*)obj_hdr, jump)) == NULL)
			return (-1);
		hdr_ext = 1;
	}
	else
	{
		jump = sizeof(*obj_hdr);
		if ((vault->f_dump = offset_jumper(vault, (void*)obj_hdr, jump)) == NULL)
			return (-1);
		hdr_ext = 0;
	}
	
	vault->header = vault->f_dump;
	if (*(unsigned int*)vault->header == MH_MAGIC_64)
	{
		iter_cmds(vault);
		print_object_path(vault, obj_hdr, path, hdr_ext);
		display_list(vault);
		free_useless_vault_components(vault);
		reset_tab_sym_meta(vault);
	}
	else if (*(unsigned int*)vault->header == MH_MAGIC)
	{
		iter_cmds_32(vault);
		print_object_path(vault, obj_hdr, path, hdr_ext);
		display_list_32(vault);
		free_useless_vault_components(vault);
		reset_tab_sym_meta(vault);
	}
	
	i = 1;
	while (i < arch->nbr_obj)
	{
		jump = sizeof(*obj_hdr) + ft_atoi(obj_hdr->ar_size);
		if ((obj_hdr = offset_jumper(vault, obj_hdr, jump)) == NULL)
			return (-1);

		if (ft_strncmp(obj_hdr->ar_name, AR_EFMT1, 2) == 0)
		{
			jump = sizeof(*obj_hdr) + ft_atoi(&obj_hdr->ar_name[3]);
			if ((vault->f_dump = offset_jumper(vault, obj_hdr, jump)) == NULL)
				return (-1);
			hdr_ext = 1;
		}
		else
		{
			if ((vault->f_dump = offset_jumper(vault, obj_hdr, sizeof(*obj_hdr))) == NULL)
				return (-1);
			hdr_ext = 0;
		}
		
		vault->header = vault->f_dump;
		if (*(unsigned int*)vault->header == MH_MAGIC_64)
		{
			iter_cmds(vault);
			print_object_path(vault, obj_hdr, path, hdr_ext);
			display_list(vault);
			free_useless_vault_components(vault);
			reset_tab_sym_meta(vault);
		}
		else if (*(unsigned int*)vault->header == MH_MAGIC)
		{
			iter_cmds_32(vault);
			print_object_path(vault, obj_hdr, path, hdr_ext);
			display_list_32(vault);
			free_useless_vault_components(vault);
			reset_tab_sym_meta(vault);
		}
		i++;
	}
	return (1);
}

int		handle_arch(t_vault *vault, char *path)
{
	t_arch_info	*arch_info;
	arch_info = malloc(sizeof(struct s_arch_info));
	if (offset_init(vault, arch_info) == -1)
		return (-1);
	if (get_nbr_symbols(vault, arch_info) == -1)
		return (-1);
	jump_obj_hdr(vault, arch_info, path);
	return (1);
}