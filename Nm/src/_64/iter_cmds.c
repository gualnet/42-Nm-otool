/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 20:51:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	 alloc_tab_sym_meta(t_vault *vault, struct symtab_command *symtab_cmd)
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

size_t	ft_strlen_cap(t_vault *vault, const char *s)
{
	size_t	i;
	void	*start_adr;
	void	*max_adr;
	void	*cur_adr;

	i = 0;
	start_adr = (vault->ar_dump != NULL) ? vault->ar_dump : vault->f_dump;
	max_adr = (void*)start_adr + vault->f_stat.st_size;
	while (s[i] != '\0')
	{
		i++;
		cur_adr = ((void*)s + i);
		if (cur_adr == max_adr)
			break;
	}
	return (i);
}

int		symtab_loop(t_vault *vault, struct symtab_command *symtab_cmd, void *strtab, struct nlist_64 *nlist)
{
	unsigned int			i;
	int						j;
	char 					*str;
	int						lenstr;
	
	i = 0;
	j = 0;

	while (i < symtab_cmd->nsyms)
	{
		if ((str = offset_jumper(vault, strtab, nlist[i].n_un.n_strx)) == NULL)
			return (-1);
		if (nlist[i].n_un.n_strx != 0)
		{
			if ((lenstr = ft_strlen_cap(vault, str)) > 1000)
				lenstr = 1000;
			vault->tab_sym_meta[j]->name = malloc(lenstr + 1 * sizeof(char));
			ft_strncpy(vault->tab_sym_meta[j]->name, str, lenstr);
			vault->tab_sym_meta[j]->name[lenstr] = '\0';
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
	// ft_printf("\nCALL HANDLE_SIMTAB\n");
	void					*strtab;
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*nlist;
	
	symtab_cmd = (void*)lc;
	nlist = offset_jumper(vault, vault->f_dump, symtab_cmd->symoff);
	strtab = offset_jumper(vault, vault->f_dump, symtab_cmd->stroff);
	if (nlist == NULL || strtab == NULL)
		return (-1);
	vault->nsyms = symtab_cmd->nsyms;
	if (alloc_tab_sym_meta(vault, symtab_cmd) == -1)
		return (-1);
	if (symtab_loop(vault, symtab_cmd, strtab, nlist) == -1)
		return (-1);
	sort_alnum(vault, symtab_cmd->nsyms);
	return (1);
}

int		inter_cmds(t_vault *vault)
{
	// ft_printf("\nCALL INTER_CMDS\n");
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	
	i = 0;
	header = vault->header;
	lc = offset_jumper(vault, vault->f_dump, sizeof(*header));
	while (i < header->ncmds)
	{
		add_new_lclink(vault, lc);
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
	// ft_printf("\nEND INTER_CMDS\n");
}