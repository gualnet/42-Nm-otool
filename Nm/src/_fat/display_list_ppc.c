/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_list_ppc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:07:46 by galy              #+#    #+#             */
/*   Updated: 2018/04/20 14:15:20 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		lssi_2_ppc(t_vault *vault, t_lc_lnk *lc_lnk, struct load_command *lc)
{
	struct segment_command	*segcmd;
	struct section			*seccmd;
	unsigned int				i;

	segcmd = (void*)lc;
	seccmd = offset_jumper(vault, lc, sizeof(struct segment_command));
	i = 0;
	while (i < swap_endian(segcmd->nsects))
	{
		if (seccmd == NULL)
			return (-1);
		if ((add_new_sectlnk(lc_lnk, seccmd)) == NULL)
		{
			ft_printf("echec display.c line 56\n");
			return (-1);
		}
		seccmd = offset_jumper(vault, seccmd, sizeof(struct section));
		i++;
	}
	return (1);
}

int		load_seg_sect_inlist_ppc(t_vault *vault)
{
	t_lc_lnk	*tmp;

	tmp = vault->lc_lst;
	while (tmp != NULL)
	{
		if (swap_endian(tmp->lc->cmd) == LC_SEGMENT)
		{
			if (lssi_2_ppc(vault, tmp, tmp->lc) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		display_list_ppc(t_vault *vault)
{
	// ft_printf("\nCALL DISPLAY_LIST\n");
	unsigned int	i;
	int				j;
	char			letter;
	
	i = 0;
	j = 0;
	if (load_seg_sect_inlist_ppc(vault) == -1)
		return (-1);
	while (i < vault->nsyms)
	{		
		letter = '?';
		letter = print_sym_sect_ppc(vault, i);
		if (letter != '?' && letter != 'N' && letter != 'I')
			ft_printf("%08llx ",swap_endian(vault->tab_sym_meta[i]->n_value));
		else
			ft_printf("%-9s", "");
		ft_printf("%c ", letter);
		ft_printf("%s\n", vault->tab_sym_meta[i]->name);	
		i++;
	}
	return (1);
	// ft_printf("\nEND DISPLAY_LIST\n");
}
