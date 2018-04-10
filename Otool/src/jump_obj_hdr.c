/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_obj_hdr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:47:38 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 12:23:02 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char	*extract_file_name(char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	while (i > 0)
	{
		if (path[i] == '/')
			return (path + i + 1);
		i--;
	}
	return (path);
}

void	print_object_path(t_vault* vault, struct ar_hdr *obj_hdr, char *path)
{
	char *o_name;

	ft_printf("%s", extract_file_name(path));
	if (ft_strncmp(obj_hdr->ar_name, AR_EFMT1, 2) == 0)
	{
		o_name = offset_jumper(vault, obj_hdr, sizeof(struct ar_hdr));
		ft_printf("(");
		read_undelimited_str(o_name, LONG_NAME_SIZE);
		ft_printf("):\n");
	}
	else
	{
		o_name = (void*)obj_hdr->ar_name;
		ft_printf("(");
		read_undelimited_str(o_name, AR_NAME_SIZE);
		ft_printf("):\n");
	}
	
}

void 	*first_jump(t_vault *vault, t_arch_info *arch_i)
{
	struct ar_hdr	*obj_hdr;
	long			jump;

	jump = sizeof(*arch_i->symtab_hdr) + ft_atoi(arch_i->symtab_hdr->ar_size) + SARMAG;
	if ((obj_hdr = offset_jumper(vault, vault->ar_dump, jump)) == NULL)
		return (NULL);
	
	// print_offset(vault, obj_hdr);
	
	return (obj_hdr);
}

void	*next_jump(t_vault *vault, struct ar_hdr *obj_hdr)
{
	struct ar_hdr	*next_obj_hdr;
	long			jump;

	vault->o_dump = NULL;

	jump = sizeof(*obj_hdr) + ft_atoi(obj_hdr->ar_size);	
	if ((next_obj_hdr = offset_jumper(vault, obj_hdr, jump)) == NULL)
		return (NULL);
	jump = sizeof(struct ar_hdr);
	vault->o_dump = offset_jumper(vault, next_obj_hdr, jump);
	if (ft_strncmp(next_obj_hdr->ar_name, AR_EFMT1, 2) == 0)
		vault->o_dump += LONG_NAME_SIZE;
	
	// void* truc = vault->o_dump;
	// vault->o_dump = NULL;
	// print_offset(vault, obj_hdr);
	// vault->o_dump = truc;

	
	return (next_obj_hdr);
}

int		inner_arch_check_magic(t_vault *vault)
{
	unsigned int magic_num;
	
	magic_num = *(unsigned int *)vault->o_dump;
	if (magic_num == MH_MAGIC_64 || magic_num == MH_CIGAM_64)
		vault->file_nfo += M_64B;
	else if (magic_num == MH_MAGIC || magic_num == MH_CIGAM)
		vault->file_nfo += M_32B;
	else
		return (-1);
	return (1);
}

int		jump_obj_hdr(t_vault *vault, t_arch_info *arch_i, char *path)
{
	struct ar_hdr	*obj_hdr;
	unsigned int	i;
	
	i = 1;
	obj_hdr = first_jump(vault, arch_i);
	vault->o_dump = (void*)obj_hdr + sizeof(struct ar_hdr);
	if (inner_arch_check_magic(vault) == -1)
		return (-1);
	print_object_path(vault, obj_hdr, path);
	if (handle_64(vault) == -1)
		return (-1);
	while (i < arch_i->nbr_obj)
	{
		if ((obj_hdr = next_jump(vault, obj_hdr)) == NULL)
			return (-1);
		print_object_path(vault, obj_hdr, path);
		handle_64(vault);
		i++;
		// if (i > 7)
		// 	exit(-1);
		// 	// break;
	}

	// vault->o_dump = check_extended_header(vault);
	// print_offset(vault, vault->o_dump);
	return (0);
}