/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:16:41 by galy              #+#    #+#             */
/*   Updated: 2018/03/15 12:10:44 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

search_seg_sect_name(t_vault *vault)
{
	t_lc_lnk *
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
		ft_printf("defined in section number n_sect ");
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

	ft_printf("test\n");
	ft_printf("N_STAB [%b]\n",N_STAB);
	ft_printf("N_PEXT [%b]\n",N_PEXT);
	ft_printf("N_TYPE [%b]\n",N_TYPE);
	ft_printf("N_EXT [%b]\n",N_EXT);
	
	while (i < vault->nsyms)
	{
		print_sym_sect(vault, i);
		ft_printf("%s\n", vault->tab_sym_meta[i]->name);
		ft_printf("vault->tab_sym_meta[%d]	->n_sect[0x0%x][%b] \n",vault->tab_sym_meta[i]->n_sect ,vault->tab_sym_meta[i]->n_sect);
		ft_printf("vault->tab_sym_meta[%d]	->n_type[0x0%x][%b] \n",vault->tab_sym_meta[i]->n_type ,vault->tab_sym_meta[i]->n_type);
		
		i++;
		ft_printf("\n");
	}
	ft_printf("\nEND DISPLAY_LIST\n");
}