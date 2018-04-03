/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vault_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 20:59:32 by galy              #+#    #+#             */
/*   Updated: 2018/04/03 19:31:31 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	reset_tab_sym_meta(t_vault *vault)
{
	uint i;

	i = 0;
	if (vault->tab_sym_meta != NULL)
	{
		while (i < vault->nsyms && vault->tab_sym_meta != NULL)
		{
			// ft_printf("vault->tab_sym_meta->name %s \n", vault->tab_sym_meta[i]->name);
			free(vault->tab_sym_meta[i]);
			i++;
		}
		free(vault->tab_sym_meta);
		vault->tab_sym_meta = NULL;
	}
}

void	loop_reinit(t_vault *vault)
{
	ft_printf("vault->f_stat [%p]\n", vault->f_stat);
	ft_printf("vault->f_stat.st_size [%lld]\n", vault->f_stat.st_size);
	munmap(vault->f_dump, vault->f_stat.st_size);
	vault->f_dump = NULL;
	vault->ar_dump = NULL;
	vault->header = NULL;
	if (vault->file_nfo == 0x01 || vault->file_nfo == 0x05)
		delete_all_lst_32(vault);
	else if (vault->file_nfo == 0x02 || vault->file_nfo == 0x06)
		delete_all_lst(vault);
}

void	*init_vault(t_vault *vault)
{
	t_vault *init;

	if (vault != NULL)
	{
		loop_reinit(vault);
		return (vault);	
	}
	if ((init = malloc(sizeof(t_vault))) == NULL)
	{
		ft_printf("\033[31mnm (init.c - line 19) error :\nmalloc vault struct space FAILED\033[0m\n");
		to_exit(NULL);
	}
	init->ar_dump = NULL;
	init->f_dump = NULL;
	init->header = NULL;
	init->lc_lst = NULL;
	init->tab_sym_meta = NULL;
	init->file_nfo = 0;
	init->nsyms = 0;
	return (init);

}