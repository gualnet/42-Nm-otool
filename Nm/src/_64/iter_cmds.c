/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/05/10 19:14:20 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		alloc_tab_sym_meta(t_vault *vault, struct symtab_command *symtab_cmd)
{
	unsigned int	i;

	if ((vault->tab_sym_meta = malloc(symtab_cmd->nsyms * \
	sizeof(void*))) == NULL)
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

int		sl_2(t_vault *vault, char *str, int j)
{
	int	lenstr;

	if ((lenstr = ft_strlen_cap(vault, str)) > 1000)
		lenstr = 1000;
	if ((vault->tab_sym_meta[j]->name = \
	malloc(lenstr + 1 * sizeof(char))) == NULL)
		return (-1);
	ft_strncpy(vault->tab_sym_meta[j]->name, str, lenstr);
	vault->tab_sym_meta[j]->name[lenstr] = '\0';
	return (0);
}

int		symtab_loop(t_vault *vault, struct symtab_command *symtab_cmd, \
struct nlist_64 *nlist)
{
	unsigned int	i;
	char			*str;
	int				j;

	i = 0;
	j = 0;
	while (i < symtab_cmd->nsyms)
	{
		if ((str = offset_jumper(vault, vault->strtab, \
		nlist[i].n_un.n_strx)) == NULL)
			return (-1);
		if (nlist[i].n_un.n_strx != 0)
		{
			if (sl_2(vault, str, j) == -1)
				return (-1);
			vault->tab_sym_meta[j]->n_sect = nlist[i].n_sect;
			vault->tab_sym_meta[j]->n_type = nlist[i].n_type;
			vault->tab_sym_meta[j]->n_value = nlist[i].n_value;
			j++;
		}
		i++;
	}
	return (1);
}

int		handle_symtab(t_vault *vault, struct load_command *lc)
{
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*nlist;

	symtab_cmd = (void*)lc;
	nlist = offset_jumper(vault, vault->f_dump, symtab_cmd->symoff);
	if (nlist == NULL)
		return (-1);
	vault->strtab = offset_jumper(vault, vault->f_dump, symtab_cmd->stroff);
	if (vault->strtab == NULL)
		return (-1);
	vault->nsyms = symtab_cmd->nsyms;
	if (alloc_tab_sym_meta(vault, symtab_cmd) == -1)
		return (-1);
	if (symtab_loop(vault, symtab_cmd, nlist) == -1)
		return (-1);
	sort_alnum(vault, symtab_cmd->nsyms);
	return (1);
}

int		iter_cmds(t_vault *vault)
{
	u_int32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = vault->header;
	if ((lc = offset_jumper(vault, vault->f_dump, sizeof(*header))) == NULL)
		return (-1);
	while (i < header->ncmds)
	{
		add_new_lclink(vault, lc);
		if (lc->cmd == LC_SEGMENT_64)
			vault->nbr_sect += ((struct segment_command_64*)lc)->nsects;
		if (lc->cmd == LC_SYMTAB)
		{
			if (handle_symtab(vault, lc) == -1)
				return (-1);
		}
		if ((lc = offset_jumper(vault, lc, lc->cmdsize)) == NULL)
			return (-1);
		i++;
	}
	return (1);
}
