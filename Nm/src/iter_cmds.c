/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/03/13 15:16:28 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*alloc_tab_symstr(struct symtab_command *symtab_cmd)
{
	char **tab;

	if ((tab = malloc(symtab_cmd->nsyms * sizeof(char*))) == NULL)
	{
		ft_printf("\nEchec malloc iter_cmds.c line 19\n");
		return (NULL);
	}
	return (tab);
}

void	symtab_loop(char **tab_symstr, struct symtab_command *symtab_cmd, void *strtab, struct nlist_64 *nlist)
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
			// ft_printf("[i:%d][%s] \n", i, str);
			// ft_printf("[n_strx:%lld] \n", nlist[i].n_un.n_strx);
			tab_symstr[j] = malloc((ft_strlen(str) + 1) * sizeof(char));
			ft_strcpy(tab_symstr[j], str);
			tab_symstr[j][ft_strlen(str)] = '\0';
			j++;
		}
		i++;
	}
}

void	handle_symtab(t_vault *vault, struct load_command *lc)
{
	ft_printf("\nCALL HANDLE_SIMTAB\n");

	
	void					*strtab;
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*nlist;
	char 					**tab_symstr;

	symtab_cmd = (void*)lc;
	nlist = (void*) vault->f_dump + symtab_cmd->symoff;
	strtab = (void*) vault->f_dump + symtab_cmd->stroff;
	print_symtab_command(symtab_cmd);
	tab_symstr = alloc_tab_symstr(symtab_cmd);
	symtab_loop(tab_symstr, symtab_cmd, strtab, nlist);

	uint i = 0;
	while (i < symtab_cmd->nsyms) // pour test
	{
		ft_printf("->%s<-\n", tab_symstr[i]);
		i++;
	}
	ft_printf("\n\n");
	sort_alnum(tab_symstr, symtab_cmd->nsyms);
}

void	inter_cmds(t_vault *vault)
{
	ft_printf("\nCALL INTER_CMDS\n");
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	// char					**tab_symstr;

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
			handle_symtab(vault, lc);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	ft_printf("\nEND\n");
}