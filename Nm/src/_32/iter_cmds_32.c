/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds_32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 04:49:07 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 20:36:03 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	 alloc_tab_sym_meta_32(t_vault *vault, struct symtab_command *symtab_cmd)
{
	// ft_printf("\nCALL ALLOC_TAB_SYM_META\n");
	unsigned int	i;

	if ((vault->tab_sym_meta = malloc(symtab_cmd->nsyms * sizeof(void*))) == NULL)
	{
		ft_printf("\nEchec malloc iter_cmds.c line 19\n");
		return (-1);
	}
	i = 0;
	while (i < symtab_cmd->nsyms)
	{
		if ((vault->tab_sym_meta[i] = malloc(sizeof(t_sym_meta))) == NULL)
		{
			ft_printf("\nEchec malloc iter_cmds.c line 28\n");
			return (-1);
		}
		i++;
	}
	return (1);	
}

int		symtab_loop_32(t_vault *vault, struct symtab_command *symtab_cmd, void *strtab, struct nlist *nlist)
{
	unsigned int	i;
	int				j;
	char 			*str;
	
	i = 0;
	j = 0;
	while (i < symtab_cmd->nsyms)
	{
		if ((str = offset_jumper(vault, strtab, nlist[i].n_un.n_strx)) == NULL)
			return (-1);
		if (nlist[i].n_un.n_strx != 0)
		{
			if ((vault->tab_sym_meta[j]->name = malloc((ft_strlen(str) + 1) * sizeof(char))) == NULL)
				return (-1);
			ft_strcpy(vault->tab_sym_meta[j]->name, str);
			vault->tab_sym_meta[j]->name[ft_strlen(str)] = '\0';
			vault->tab_sym_meta[j]->n_sect = nlist[i].n_sect;
			vault->tab_sym_meta[j]->n_type = nlist[i].n_type;
			vault->tab_sym_meta[j]->n_value = nlist[i].n_value;
			j++;
		}
		i++;
	}
	return (1);
}

int		handle_symtab_32(t_vault *vault, struct load_command *lc)
{
	// ft_printf("\nCALL HANDLE_SIMTAB\n");
	void					*strtab;
	struct symtab_command	*symtab_cmd;
	struct nlist			*nlist;
	
	symtab_cmd = (void*)lc;
	nlist = offset_jumper(vault, vault->f_dump, symtab_cmd->symoff);
	strtab = offset_jumper(vault, vault->f_dump, symtab_cmd->stroff);
	vault->nsyms = symtab_cmd->nsyms;
	if (alloc_tab_sym_meta_32(vault, symtab_cmd) == -1)
		return (-1);
	if (symtab_loop_32(vault, symtab_cmd, strtab, nlist) == -1)
		return (-1);
	sort_alnum(vault, symtab_cmd->nsyms);
	return (1);
}

int		inter_cmds_32(t_vault *vault)
{
	// ft_printf("\nCALL INTER_CMDS\n");
	unsigned int			i;
	struct mach_header		*header;
	struct load_command		*lc;
	
	i = 0;
	header = vault->header;
	lc = offset_jumper(vault, vault->f_dump, sizeof(*header));
	while (i < header->ncmds)
	{
		if (lc == NULL)
			return (-1);
		add_new_lclink_32(vault, lc);
		if (lc->cmd == LC_SYMTAB)
		{
			if (handle_symtab_32(vault, lc) == -1)
				return (-1);
		}
		lc = offset_jumper(vault, lc, lc->cmdsize);
		i++;
	}
	return (1);
	// ft_printf("\nEND INTER_CMDS\n");
}