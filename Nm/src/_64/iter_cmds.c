/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/04/04 15:48:47 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void alloc_tab_sym_meta(t_vault *vault, struct symtab_command *symtab_cmd)
{
	// ft_printf("\nCALL ALLOC_TAB_SYM_META\n");
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

size_t	ft_strlen_cap(t_vault *vault, const char *s)
{
	size_t	i;
	void	*start_adr;
	void	*max_adr;

	i = 0;
	ft_printf("001\n");
	start_adr = (vault->ar_dump != NULL) ? vault->ar_dump : vault->f_dump;
	max_adr = (void*)start_adr + vault->f_stat.st_size;
	ft_printf("002\n");
	while (s[i] != '\0')
	{
		// if (((void*)s + i) > max_adr)
		// 	break;
		i++;
		if (((void*)s + i) > max_adr)
			break;
	}
	ft_printf("003\n");
	return (i);
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
		// str = (char*)(strtab + nlist[i].n_un.n_strx);
		str = offset_jumper(vault, strtab, nlist[i].n_un.n_strx);
		if (nlist[i].n_un.n_strx != 0)
		{
			int lenstr = 0;
			lenstr = ft_strlen_cap(vault, str);
			void *alloc = malloc(lenstr + 1 * sizeof(char));
			// void *alloc = malloc(25000 * sizeof(char));
			vault->tab_sym_meta[j]->name = alloc;
			// vault->tab_sym_meta[j]->name = malloc((ft_strlen(str) + 1) * sizeof(char));
			ft_strncpy(vault->tab_sym_meta[j]->name, str, lenstr);
			vault->tab_sym_meta[j]->name[lenstr] = '\0';
			vault->tab_sym_meta[j]->n_sect = nlist[i].n_sect;
			vault->tab_sym_meta[j]->n_type = nlist[i].n_type;
			vault->tab_sym_meta[j]->n_value = nlist[i].n_value;
			// ft_printf("%016x %s\n", vault->tab_sym_meta[j]->n_value, vault->tab_sym_meta[j]->name);
			j++;
		}
		i++;
	}
}

void	handle_symtab(t_vault *vault, struct load_command *lc)
{
	// ft_printf("\nCALL HANDLE_SIMTAB\n");

	void					*strtab;
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*nlist;
	
	symtab_cmd = (void*)lc;
	// nlist = (void*) vault->f_dump + symtab_cmd->symoff;
	nlist = offset_jumper(vault, vault->f_dump, symtab_cmd->symoff);
	// strtab = (void*) vault->f_dump + symtab_cmd->stroff;
	strtab = offset_jumper(vault, vault->f_dump, symtab_cmd->stroff);
	vault->nsyms = symtab_cmd->nsyms;
	// print_symtab_command(symtab_cmd);
	alloc_tab_sym_meta(vault, symtab_cmd);
	symtab_loop(vault, symtab_cmd, strtab, nlist);
	sort_alnum(vault, symtab_cmd->nsyms);
}

void	inter_cmds(t_vault *vault)
{
	// ft_printf("\nCALL INTER_CMDS\n");
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	
	i = 0;
	header = vault->header;
	// ft_printf("sizeof(struct mach_header_64) [%d]\n", sizeof(*header));
	// lc = (void*)vault->f_dump + sizeof(*header);
	lc = offset_jumper(vault, vault->f_dump, sizeof(*header));
	// ft_printf("vault->f_dump [%p]\n", vault->f_dump);
	// ft_printf("vault->header_64->ncmds [%d]\n", header->ncmds);
	while (i < header->ncmds)
	{
		// ft_printf("lc [%p]\n", lc);
		// print_offset(vault, lc);
		// ft_printf("[%d]lc->cmd [%x]\n", i, lc->cmd);
		// ft_printf("lc->cmdsize [%x]\n", lc->cmdsize);
		add_new_lclink(vault, lc);
		// print_offset(vault, lc);
		// ft_printf("000\n");
		// ft_printf("lc->cmd[%p]\n", lc->cmd);
		// ft_printf("000\n");
		if (lc->cmd == LC_SYMTAB)
		{
			// ft_printf("001\n");
			handle_symtab(vault, lc);
			// ft_printf("002\n");
		}
		// ft_printf("003\n");
		// lc = (void*)lc + lc->cmdsize;
		// ft_printf("jump of lc->cmdsize [%d]\n", lc->cmdsize);
		// print_offset(vault, lc);
		lc = offset_jumper(vault, lc, lc->cmdsize);
		i++;
	}
	// ft_printf("\nEND INTER_CMDS\n");
}