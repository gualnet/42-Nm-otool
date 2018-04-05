/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vault_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 09:08:16 by galy              #+#    #+#             */
/*   Updated: 2018/04/05 10:10:04 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	*init_vault(t_vault *vault)
{
	t_vault *init;

	if (vault != NULL)
	{
		ft_printf("NEED LOOP\n");
		exit(-1);
		// loop_reinit(vault);
		return (vault);	
	}
	if ((init = malloc(sizeof(t_vault))) == NULL)
	{
		ft_printf("\033[31mnm (init.c - line 19) error :\nmalloc vault struct space FAILED\033[0m\n");
		exit(-1);
		// to_exit(NULL);
	}
	init->fat_dump = NULL;
	init->ar_dump = NULL;
	init->o_dump = NULL;
	init->file_nfo = 0;
	init->option = 0;
	return (init);
}
