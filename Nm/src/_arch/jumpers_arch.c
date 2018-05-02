/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jumpers_arch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:33:00 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 20:00:27 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		jmp_step_1(t_vault *vault, t_arch_info *arch, struct ar_hdr	**obj_hdr)
{
	long	jump;

	jump = sizeof(*arch->off_symtab_hdr) + \
	ft_atoi(arch->off_symtab_hdr->ar_size);
	if (((*obj_hdr) = offset_jumper(vault, arch->off_symtab_hdr, jump)) == NULL)
		return (-1);
	if (ft_strncmp((*obj_hdr)->ar_name, AR_EFMT1, 2) == 0)
	{
		jump = sizeof(*(*obj_hdr)) + ft_atoi(&(*obj_hdr)->ar_name[3]);
		if ((vault->f_dump = offset_jumper(vault, (void*)(*obj_hdr), \
		jump)) == NULL)
			return (-1);
		return (1);
	}
	else
	{
		jump = sizeof(*(*obj_hdr));
		if ((vault->f_dump = offset_jumper(vault, (void*)(*obj_hdr), \
		jump)) == NULL)
			return (-1);
		return (0);
	}
	return (-1);
}

int		jmp_step_2(t_vault *vault, struct ar_hdr **obj_hdr)
{
	long	jump;

	jump = sizeof(*(*obj_hdr)) + ft_atoi((*obj_hdr)->ar_size);
	if (((*obj_hdr) = offset_jumper(vault, (*obj_hdr), jump)) == NULL)
		return (-1);
	if (ft_strncmp((*obj_hdr)->ar_name, AR_EFMT1, 2) == 0)
	{
		jump = sizeof(*(*obj_hdr)) + ft_atoi(&(*obj_hdr)->ar_name[3]);
		if ((vault->f_dump = offset_jumper(vault, (*obj_hdr), jump)) == NULL)
			return (-1);
		return (1);
	}
	else
	{
		if ((vault->f_dump = offset_jumper(vault, (*obj_hdr), \
		sizeof(*(*obj_hdr)))) == NULL)
			return (-1);
		return (0);
	}
	return (-1);
}

void	print_and_clean_routine(t_vault *vault, struct ar_hdr **obj_hdr, \
char *path, char hdr_ext)
{
	vault->header = vault->f_dump;
	if (*(unsigned int*)vault->header == MH_MAGIC_64)
	{
		iter_cmds(vault);
		print_object_path(vault, *obj_hdr, path, hdr_ext);
		display_list(vault);
		free_useless_vault_components(vault);
		reset_tab_sym_meta(vault);
	}
	else if (*(unsigned int*)vault->header == MH_MAGIC)
	{
		iter_cmds_32(vault);
		print_object_path(vault, *obj_hdr, path, hdr_ext);
		display_list_32(vault);
		free_useless_vault_components(vault);
		reset_tab_sym_meta(vault);
	}
}

int		jump_obj_hdr(t_vault *vault, t_arch_info *arch, char *path)
{
	struct ar_hdr	*obj_hdr;
	unsigned int	i;
	char			hdr_ext;

	if ((hdr_ext = jmp_step_1(vault, arch, &obj_hdr)) == -1)
		return (-1);
	print_and_clean_routine(vault, &obj_hdr, path, hdr_ext);
	i = 1;
	while (i < arch->nbr_obj)
	{
		if ((hdr_ext = jmp_step_2(vault, &obj_hdr)) == -1)
			return (-1);
		print_and_clean_routine(vault, &obj_hdr, path, hdr_ext);
		i++;
	}
	return (1);
}
