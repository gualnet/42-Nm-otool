/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_list_64_swap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:16:41 by galy              #+#    #+#             */
/*   Updated: 2018/05/03 11:26:58 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		lssi_2_64_swap(t_vault *vault, t_lc_lnk *lc_lnk, \
struct load_command *lc)
{
	struct segment_command_64	*segcmd;
	struct section_64			*seccmd;
	unsigned int				i;

	segcmd = (void*)lc;
	if ((seccmd = offset_jumper(vault, lc, sizeof(*segcmd))) == NULL)
		return (-1);
	i = 0;
	while (i < segcmd->nsects)
	{
		if ((add_new_sectlnk(lc_lnk, seccmd)) == NULL)
		{
			ft_printf("echec display.c line 56\n");
			return (-1);
		}
		if ((seccmd = offset_jumper(vault, seccmd, sizeof(*seccmd))) == NULL)
			return (-1);
		i++;
	}
	return (1);
}

int		load_seg_sect_inlist_64_swap(t_vault *vault)
{
	t_lc_lnk	*tmp;

	tmp = vault->lc_lst;
	while (tmp != NULL)
	{
		if (tmp->lc->cmd == LC_SEGMENT_64)
		{
			if (lssi_2_64_swap(vault, tmp, tmp->lc) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	dl64s_in(t_vault *vault, char letter, unsigned int i)
{
	void			*indr_str;

	if (letter != '?' && letter != 'N')
	{
		if (letter != 'U' && letter != 'I')
			ft_printf("%016llx ", vault->tab_sym_meta[i]->n_value);
		else
			ft_printf("%-17s", "");
		if (letter != 'I')
		{
			ft_printf("%c ", letter);
			ft_printf("%s\n", vault->tab_sym_meta[i]->name);
		}
		if (letter == 'I')
		{
			if ((indr_str = get_indirection_name(vault, i)) == NULL)
				indr_str = &("unknown");
			ft_printf("%c ", letter);
			ft_printf("%s ", vault->tab_sym_meta[i]->name);
			ft_printf("(indirect for %s)\n", indr_str);
		}
	}
}

int		display_list_64_swap(t_vault *vault)
{
	unsigned int	i;
	char			letter;

	i = 0;
	if (load_seg_sect_inlist_64_swap(vault) == -1)
		return (-1);
	while (i < vault->nsyms)
	{
		letter = '?';
		letter = print_sym_sect_64_swap(vault, i);
		dl64s_in(vault, letter, i);
		i++;
	}
	return (1);
}
