/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ppc_in_fat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:46:07 by galy              #+#    #+#             */
/*   Updated: 2018/04/17 12:17:32 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_ppc_in_fat(t_vault *vault, char *path)
{
	ft_printf("CALL PPC IN FAT");
	if (inter_cmds_ppc(vault) == -1)
		return (-1);
	ft_printf("\n%s (for architecture ppc):\n", path);
	if (display_list_32(vault) == -1)
		return (-1);
	return (1);
}