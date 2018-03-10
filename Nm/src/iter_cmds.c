/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/03/10 13:51:22 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_simtab(t_vault *vault)
{
	

	
}

void	inter_cmds(t_vault *vault)
{
	ft_printf("\nCALL INTER_CMDS\n");
	uint32_t				i;
	struct load_command		*lc;
	// struct symtab_command	*syc

	i = 0;
	// ft_printf("sizeof(struct mach_header_64) [%d]\n", sizeof(struct mach_header_64));
	// lc = vault->f_buff + sizeof(struct mach_header_64);
	ft_printf("sizeof(struct mach_header_64) [%d]\n", sizeof(vault->header->_64));
	lc = vault->f_buff + sizeof(vault->header->_64);

	ft_printf("vault->header_64.ncmds [%d]\n", vault->header->_64.ncmds);
	ft_printf("lc->cmdsize [%d]\n", lc->cmdsize);
	while (i < vault->header->_64.ncmds)
	{
		// ft_printf("\n1{%p} - 2{%p}\n\n", lc+ lc->cmdsize, (void*)lc+ lc->cmdsize);
		// ft_printf("i {%d} - {%p}lc->cmd {%x}{%d}\n", i, lc, lc->cmd, lc->cmdsize);
		if (lc->cmd == LC_SYMTAB)
		{
			ft_printf("BINGO\n");
			handle_simtab(vault);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	ft_printf("END\n");
}
