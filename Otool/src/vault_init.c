/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vault_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 09:08:16 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 19:12:22 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	*re_init_vault(t_vault *vault)
{
	if (vault == NULL)
		return (NULL);
	if (vault->fat_dump != NULL)
		free(vault->fat_dump);
	vault->fat_dump = NULL;
	if (vault->ar_dump != NULL)
		free(vault->ar_dump);
	vault->ar_dump = NULL;
	if (vault->o_dump != NULL && \
	(((vault->file_nfo & M_FAT) == 0) && ((vault->file_nfo & M_ARCH) == 0)))
		free(vault->o_dump);
	vault->o_dump = NULL;
	vault->sect_hdr = NULL;
	vault->sect = NULL;
	vault->file_nfo = 0;
	return (vault);
}

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
		ft_printf("\033[31mnm (init.c - line 19) error :"
		"\nmalloc vault struct space FAILED\033[0m\n");
		return (NULL);
	}
	init->fat_dump = NULL;
	init->ar_dump = NULL;
	init->o_dump = NULL;
	init->sect_hdr = NULL;
	init->sect = NULL;
	init->file_nfo = 0;
	init->option = 0;
	return (init);
}
