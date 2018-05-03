/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ppc_in_fat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:46:07 by galy              #+#    #+#             */
/*   Updated: 2018/05/03 11:35:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*dump_endian_reverse_ppc(t_vault *vault, size_t size)
{
	size_t	i;
	void	*dump;
	void	*tete;
	void	*ppc;

	i = 0;
	tete = NULL;
	if ((dump = malloc(size)) == NULL)
		return (NULL);
	ppc = vault->f_dump;
	ft_bzero(dump, size);
	while (i * 4 < size)
	{
		*(int*)(dump + (int)tete) = swap_endian(*(int*)(ppc + (int)tete));
		tete += sizeof(int);
		i++;
	}
	return (dump);
}

int		handle_ppc_in_fat(t_vault *vault, char *path)
{
	if (iter_cmds_ppc(vault) == -1)
		return (-1);
	ft_printf("\n%s (for architecture ppc):\n", path);
	if (display_list_ppc(vault) == -1)
		return (-1);
	reset_tab_sym_meta(vault);
	delete_all_lst(vault);
	return (1);
}
