/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32_in_fat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:23:35 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:31:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_32_in_fat(t_vault *vault, char *path)
{
	if (iter_cmds_32(vault) == -1)
		return (-1);
	ft_printf("\n%s (for architecture i386):\n", path);
	if (display_list_32(vault) == -1)
		return (-1);
	reset_tab_sym_meta(vault);
	delete_all_lst(vault);
	return (1);
}
