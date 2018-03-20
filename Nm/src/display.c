/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:16:41 by galy              #+#    #+#             */
/*   Updated: 2018/03/20 19:18:37 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	lssi_2(t_lc_lnk *lc_lnk, struct load_command *lc)
{
	struct segment_command_64	*segcmd;
	struct section_64			*seccmd;
	unsigned int				i;

	segcmd = (void*)lc;
	seccmd = (void*)lc + sizeof(struct segment_command_64);
	i = 0;
	
	// ft_printf("segcmd->nsects [%d]\n",segcmd->nsects);
	while (i < segcmd->nsects)
	{

		// ft_printf("\nseccmd->segname [%s]\n",seccmd->segname);
		// ft_printf("seccmd->sectname [%s]\n",seccmd->sectname);
		if ((add_new_sectlnk(lc_lnk, seccmd)) == NULL)
		{
			ft_printf("echec display.c line 56\n");
			exit (-1);
		}
		seccmd = (void*)seccmd + sizeof(struct section_64);
		i++;
	}
}

void	load_seg_sect_inlist(t_vault *vault)
{
	t_lc_lnk	*tmp;
	// struct load_command	*lc;	

	tmp = vault->lc_lst;
	// ft_printf("vault->lc_lst [%p][%p][%p]\n",&vault->lc_lst,vault->lc_lst,*vault->lc_lst);
	while (tmp != NULL)
	{
		if (tmp->lc->cmd == LC_SEGMENT_64)
		{
			lssi_2(tmp, tmp->lc);
		}
		tmp = tmp->next;
	}
	// ft_printf("vault->lc_lst [%p][%p][%p]\n",&vault->lc_lst,vault->lc_lst,*vault->lc_lst);
}

void	display_list(t_vault *vault)
{
	ft_printf("\nCALL DISPLAY_LIST\n");
	
	unsigned int	i;
	int j;
	char letter;
	
	i = 0;
	j = 0;
	// ft_printf("vault->nsyms %d\n", vault->nsyms);
	load_seg_sect_inlist(vault);
	while (i < vault->nsyms)
	{
		
		letter = '?';
		// ft_printf("001\n");
		// ft_printf("vault->tab_sym_meta[%d]	->name[%s] \n",i, vault->tab_sym_meta[i]->name);
		// ft_printf("vault->tab_sym_meta[%d]	->n_value[%s] \n",i, vault->tab_sym_meta[i]->n_value);
		// ft_printf("vault->tab_sym_meta[%d]	->n_sect[0x0%x][%b] \n",i, vault->tab_sym_meta[i]->n_sect ,vault->tab_sym_meta[i]->n_sect);
		// ft_printf("vault->tab_sym_meta[%d]	->n_type[0x0%x][%b] \n",i, vault->tab_sym_meta[i]->n_type ,vault->tab_sym_meta[i]->n_type);
		letter = print_sym_sect(vault, i);
		// ft_printf("002\n");
		if (letter != 'U')
			ft_printf("%x ",vault->tab_sym_meta[i]->n_value);
		else
			ft_printf("%-17s", "");
		// ft_printf("003\n");

		ft_printf("%c ", letter);

		ft_printf("%s\n", vault->tab_sym_meta[i]->name);
		// ft_printf("004\n");
		// ft_printf("vault->tab_sym_meta[%d]	->n_sect[0x0%x][%b] \n",vault->tab_sym_meta[i]->n_sect ,vault->tab_sym_meta[i]->n_sect);
		// ft_printf("vault->tab_sym_meta[%d]	->n_type[0x0%x][%b] \n",vault->tab_sym_meta[i]->n_type ,vault->tab_sym_meta[i]->n_type);
		
		i++;
		// ft_printf("\n");
	}
	ft_printf("\nEND DISPLAY_LIST\n");
}