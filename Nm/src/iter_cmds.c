/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/03/28 18:07:49 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void alloc_tab_sym_meta(t_vault *vault, struct symtab_command *symtab_cmd)
{
	ft_printf("\nCALL ALLOC_TAB_SYM_META\n");
	unsigned int	i;

	// ft_printf("%p - %p\n", &vault->tab_sym_meta, vault->tab_sym_meta);
	if ((vault->tab_sym_meta = malloc(symtab_cmd->nsyms * sizeof(void*))) == NULL)
	{
		ft_printf("\nEchec malloc iter_cmds.c line 19\n");
		exit(-1);
	}
	i = 0;
	while (i < symtab_cmd->nsyms)
	{
		if ((vault->tab_sym_meta[i] = malloc(sizeof(t_sym_meta))) == NULL)
		{
			ft_printf("\nEchec malloc iter_cmds.c line 28\n");
			exit(-1);
		}
		i++;
	}	
}

void	symtab_loop(t_vault *vault, struct symtab_command *symtab_cmd, void *strtab, struct nlist_64 *nlist)
{
	unsigned int			i;
	int						j;
	char 					*str;
	
	i = 0;
	j = 0;
	while (i < symtab_cmd->nsyms)
	{
		str = (char*)(strtab + nlist[i].n_un.n_strx);
		if (nlist[i].n_un.n_strx != 0)
		{
			vault->tab_sym_meta[j]->name = malloc((ft_strlen(str) + 1) * sizeof(char));
			ft_strcpy(vault->tab_sym_meta[j]->name, str);
			vault->tab_sym_meta[j]->name[ft_strlen(str)] = '\0';
			vault->tab_sym_meta[j]->n_sect = nlist[i].n_sect;
			vault->tab_sym_meta[j]->n_type = nlist[i].n_type;
			vault->tab_sym_meta[j]->n_value = nlist[i].n_value;
			// ft_printf("%016x %s\n", vault->tab_sym_meta[j]->n_value, vault->tab_sym_meta[j]->name);
			j++;
		}
		i++;
	}
	// exit(0);
}

void	handle_symtab(t_vault *vault, struct load_command *lc)
{
	ft_printf("\nCALL HANDLE_SIMTAB\n");

	void					*strtab;
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*nlist;
	
	symtab_cmd = (void*)lc;
	nlist = (void*) vault->f_dump + symtab_cmd->symoff;
	strtab = (void*) vault->f_dump + symtab_cmd->stroff;
	vault->nsyms = symtab_cmd->nsyms;
	// print_symtab_command(symtab_cmd);
	alloc_tab_sym_meta(vault, symtab_cmd);
	symtab_loop(vault, symtab_cmd, strtab, nlist);
	sort_alnum(vault, symtab_cmd->nsyms);
}

void	inter_cmds(t_vault *vault)
{
	ft_printf("\nCALL INTER_CMDS\n");
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	
	i = 0;
	header = vault->header;
	// ft_printf("sizeof(struct mach_header_64) [%d]\n", sizeof(*header));
	lc = (void*)vault->f_dump + sizeof(*header);
	// ft_printf("vault->f_dump [%p]\n", vault->f_dump);
	// ft_printf("vault->header_64->ncmds [%d]\n", header->ncmds);
	while (i < header->ncmds)
	{
		// ft_printf("[%d]lc->cmd [%x]\n", i, lc->cmd);
		// ft_printf("lc->cmdsize [%x]\n", lc->cmdsize);
		add_new_lclink(vault, lc);
		if (lc->cmd == LC_SYMTAB)
		{
			// ft_printf("BINGO i = %d\n", i);
			handle_symtab(vault, lc);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	// ft_printf("\nEND INTER_CMDS\n");
}