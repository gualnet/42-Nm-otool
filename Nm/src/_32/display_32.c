/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 05:25:08 by galy              #+#    #+#             */
/*   Updated: 2018/04/03 19:37:14 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	lssi_2_32(t_vault *vault, t_lc_lnk *lc_lnk, struct load_command *lc)
{
	struct segment_command	*segcmd;
	struct section			*seccmd;
	unsigned int				i;

	segcmd = (void*)lc;
	// seccmd = offset_jumper(vault, lc, sizeof(struct segment_command));
	i = 0;
	while (i < segcmd->nsects)
	{
		if ((add_new_sectlnk(lc_lnk, seccmd)) == NULL)
		{
			ft_printf("echec display.c line 56\n");
			exit (-1);
		}
		seccmd = offset_jumper(vault, seccmd, sizeof(struct section));
		i++;
	}
}

void	load_seg_sect_inlist_32(t_vault *vault)
{
	t_lc_lnk	*tmp;

	tmp = vault->lc_lst;
	// ft_printf("vault->lc_lst [%p][%p][%p]\n",&vault->lc_lst,vault->lc_lst,*vault->lc_lst);
	while (tmp != NULL)
	{
		if (tmp->lc->cmd == LC_SEGMENT)
		{
			lssi_2_32(vault, tmp, tmp->lc);
		}
		tmp = tmp->next;
	}
	// ft_printf("vault->lc_lst [%p][%p][%p]\n",&vault->lc_lst,vault->lc_lst,*vault->lc_lst);
}

void	display_list_32(t_vault *vault)
{
	// ft_printf("\nCALL DISPLAY_LIST\n");
	unsigned int	i;
	int				j;
	char			letter;
	
	i = 0;
	j = 0;
	load_seg_sect_inlist_32(vault);
	while (i < vault->nsyms)
	{		
		letter = '?';
		letter = print_sym_sect_32(vault, i);
		if (letter != '@')
		{
			if (letter != 'U')
				ft_printf("%08llx ",vault->tab_sym_meta[i]->n_value);
			else
				ft_printf("%-9s", "");
			ft_printf("%c ", letter);
			ft_printf("%s\n", vault->tab_sym_meta[i]->name);	
		}
		i++;
	}
	// ft_printf("\nEND DISPLAY_LIST\n");
}