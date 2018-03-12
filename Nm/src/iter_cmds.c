/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/03/12 19:05:53 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_simtab(t_vault *vault, struct load_command *lc)
{
	ft_printf("\nCALL HANDLE_SIMTAB\n");

	unsigned int			i;
	void					*strtab;
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*nlist;
	char *str;

	symtab_cmd = (void*)lc;
	nlist = (void*) vault->f_dump + symtab_cmd->symoff;
	strtab = (void*) vault->f_dump + symtab_cmd->stroff;
	ft_printf("000\n");
	// print_symtab_command(lc);
	print_symtab_command(symtab_cmd);
	
	i = 0;
	while (i < symtab_cmd->nsyms)
	{
			// ft_printf("SYMBOLES: \n");
		str = (char*)(strtab + nlist[i].n_un.n_strx);
		if (nlist[i].n_un.n_strx != 0)
		{
			// ft_printf("-->%d \n", );	
			ft_printf("[i:%d][%s] \n", i, str);		
			// ft_printf("[n_strx:%lld] \n", nlist[i].n_un.n_strx);
			// ft_printf("\n");
		}
		i++;
	}
	// ft_printf("006\n");
	exit(-1);
}

void	inter_cmds(t_vault *vault)
{
	ft_printf("\nCALL INTER_CMDS\n");
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = vault->header;
	ft_printf("sizeof(struct mach_header_64) [%d]\n", sizeof(*header));
	lc = (void*)vault->f_dump + sizeof(*header);

	ft_printf("vault->header_64.ncmds [%d]\n", header->ncmds);
	ft_printf("lc->cmdsize [%d]\n", lc->cmdsize);
	while (i < header->ncmds)
	{
		// ft_printf("\n1{%p} - 2{%p}\n\n", lc+ lc->cmdsize, (void*)lc+ lc->cmdsize);
		// ft_printf("i {%d} - {%p}lc->cmd {%x}{%d}\n", i, lc, lc->cmd, lc->cmdsize);
		if (lc->cmd == LC_SYMTAB)
		{
			ft_printf("BINGO i = %d\n", i);
			handle_simtab(vault, lc);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	ft_printf("\nEND\n");
}