/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:16:41 by galy              #+#    #+#             */
/*   Updated: 2018/03/15 18:22:20 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// void	test(struct load_command *lc)
// {
// 	struct segment_command_64	*segcmd;
// 	struct section_64			*seccmd;

// 	segcmd = (void*)lc;
// 	ft_printf("segcmd->cmd [%x]\n", segcmd->cmd);
// 	ft_printf("segcmd->cmdsize [%x]\n", segcmd->cmdsize);
// 	ft_printf("segcmd->nsects [%d]\n\n", segcmd->nsects);

// 	uint i = 0;
// 	seccmd = (void*)lc + sizeof(struct segment_command_64);
// 	while (i < segcmd->nsects)
// 	{
// 		// ft_printf("seccmd [%p]\n",seccmd);
// 		// ft_printf("seccmd->sectname [%s]\n",seccmd->sectname);
// 		// ft_printf("seccmd->segname [%s]\n",seccmd->segname);

// 		seccmd = (void*)seccmd + sizeof(struct section_64);
// 		i++;
// 	}
// 	if (lc->cmd == LC_SEGMENT)
// 	{
		
// 	}
// }

void	lssi_2(struct load_command *lc)
{
	struct segment_command_64	*segcmd;
	struct section_64			*seccmd;
	unsigned int				i;

	segcmd = (void*)lc;
	seccmd = (void*)lc + sizeof(struct segment_command_64);
	i = 0;
	while (i < segcmd->nsects)
	{

		ft_printf("seccmd->sectname [%s]\n",seccmd->sectname);
		ft_printf("seccmd->segname [%s]\n",seccmd->segname);
		seccmd = (void*)seccmd + sizeof(struct section_64);
		i++;
	}

}

void	load_seg_sect_inlist(t_vault *vault)
{
	t_lc_lnk	*tmp;
	// struct load_command	*lc;	

	tmp = vault->lc_lst;
	ft_printf("vault->lc_lst [%p][%p][%p]\n",&vault->lc_lst,vault->lc_lst,*vault->lc_lst);
	while (tmp != NULL)
	{
		if (tmp->lc->cmd == LC_SEGMENT_64)
		{
			lssi_2(tmp->lc);
		}
		tmp = tmp->next;
	}
	ft_printf("vault->lc_lst [%p][%p][%p]\n",&vault->lc_lst,vault->lc_lst,*vault->lc_lst);
}

char	get_sect_letter(t_vault *vault, unsigned int n_sect)
{
	ft_printf("coucou\n");
	unsigned int	i;
	t_sect_lnk		*tmp;
	struct mach_header_64	*header;

	i = 0;
	tmp = vault->lc_lst->sect_lst;
	header = vault->header;
	ft_printf("0000\n");
	while (i < header->ncmds)
	{
		ft_printf("0001\n");
		ft_printf("0001 %p\n", tmp);
		if (i == n_sect)
			break;
		i++;
		ft_printf("0002\n");
		tmp = tmp->next;
		ft_printf("0003\n");
	}
	ft_printf("[%d]tmp [%s]\n", i, tmp->sect->segname);
	ft_printf("[%d]tmp [%s]\n", i, tmp->sect->sectname);
	return ('Z');
}

void	print_sym_sect(t_vault *vault, unsigned int i)
{
	if ((vault->tab_sym_meta[i]->n_type & N_STAB) != 0)
		ft_printf("SYMBOLIQUE DEBUG ENTRY?? ");
	else if ((vault->tab_sym_meta[i]->n_type & N_PEXT) == 1)
		ft_printf("private external symbol?? ");
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_UNDF)
		ft_printf("U ");
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_ABS)
		ft_printf("defined in section number n_sect?? ");
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_SECT)
		ft_printf("[%c] ", get_sect_letter(vault, vault->tab_sym_meta[i]->n_sect));
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_PBUD)
		ft_printf("prebound undefined ");
	else if ((vault->tab_sym_meta[i]->n_type & N_TYPE) == N_INDR)
		ft_printf("indirect ");

}

// #define	N_UNDF	0x0		/* undefined, n_sect == NO_SECT */
// #define	N_ABS	0x2		/* absolute, n_sect == NO_SECT */
// #define	N_SECT	0xe		/* defined in section number n_sect */
// #define	N_PBUD	0xc		/* prebound undefined (defined in a dylib) */
// #define N_INDR	0xa		/* indirect */

void	display_list(t_vault *vault)
{
	ft_printf("\nCALL DISPLAY_LIST\n");
	
	unsigned int	i;
	int j;
	i = 0;
	j = 0;
	
	// ft_printf("vault->nsyms %d\n", vault->nsyms);
	load_seg_sect_inlist(vault);
	

	// ft_printf("test\n");
	// ft_printf("N_STAB [%b]\n",N_STAB);
	// ft_printf("N_PEXT [%b]\n",N_PEXT);
	// ft_printf("N_TYPE [%b]\n",N_TYPE);
	// ft_printf("N_EXT [%b]\n",N_EXT);
	ft_printf("\n");
	
	while (i < vault->nsyms)
	{
		print_sym_sect(vault, i);
		ft_printf("%s\n", vault->tab_sym_meta[i]->name);
		// ft_printf("vault->tab_sym_meta[%d]	->n_sect[0x0%x][%b] \n",vault->tab_sym_meta[i]->n_sect ,vault->tab_sym_meta[i]->n_sect);
		// ft_printf("vault->tab_sym_meta[%d]	->n_type[0x0%x][%b] \n",vault->tab_sym_meta[i]->n_type ,vault->tab_sym_meta[i]->n_type);
		
		i++;
		// ft_printf("\n");
	}
	ft_printf("\nEND DISPLAY_LIST\n");
}