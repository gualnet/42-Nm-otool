/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:16:41 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:33:33 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		lssi_2(t_vault *vault, t_lc_lnk *lc_lnk, struct load_command *lc)
{
	struct segment_command_64	*segcmd;
	struct section_64			*seccmd;
	unsigned int				i;

	segcmd = (void*)lc;
	if ((seccmd = offset_jumper(vault, lc, sizeof(struct segment_command_64))) == NULL)
		return (-1);
	i = 0;
	while (i < segcmd->nsects)
	{
		if ((add_new_sectlnk(lc_lnk, seccmd)) == NULL)
		{
			ft_printf("echec display.c line 56\n");
			return (-1);
		}
		if ((seccmd = offset_jumper(vault, seccmd, sizeof(struct section_64))) == NULL)
			return (-1);
		i++;
	}
	return (1);
}

int		load_seg_sect_inlist(t_vault *vault)
{
	t_lc_lnk	*tmp;

	tmp = vault->lc_lst;
	while (tmp != NULL)
	{
		if (tmp->lc->cmd == LC_SEGMENT_64)
		{
			if (lssi_2(vault, tmp, tmp->lc) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		display_list(t_vault *vault)
{
	unsigned int	i;
	int				j;
	char			letter;
	
	i = 0;
	j = 0;
	if (load_seg_sect_inlist(vault) == -1)
		return (-1);
	while (i < vault->nsyms)
	{		
		letter = '?';
		letter = print_sym_sect(vault, i);
		if (letter != '?' && letter != 'N')
		{
			if (letter != 'U')
				ft_printf("%016llx ",vault->tab_sym_meta[i]->n_value);
			else
				ft_printf("%-17s", "");
			ft_printf("%c ", letter);
			ft_printf("%s\n", vault->tab_sym_meta[i]->name);	
		}
		i++;
	}
	return (1);
}
