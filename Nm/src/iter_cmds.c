/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:36:21 by galy              #+#    #+#             */
/*   Updated: 2018/02/23 21:44:10 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	inter_cmds(t_vault *vault)
{
	int						i;
	struct load_commands	*lc;

	i = 0;
	lc = vault->f_buff + sizeof(struct mach_header_64);

	ft_printf("vault->header_64.ncmds [%d]\n", vault->header_64.ncmds);
	// ft_printf("vault->header_64.ncmds [%d]\n", vault->header_64.ncmds);
	// while (i < vault->header_64.ncmds)
	// {
		
	// 	lc += lc->cmdsize;
	// 	i++;
	// }


}