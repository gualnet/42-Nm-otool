/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_inner_32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:23:35 by galy              #+#    #+#             */
/*   Updated: 2018/04/17 11:24:53 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_32_in_fat(t_vault *vault, char *path)
{
	if (inter_cmds_32(vault) == -1)
		return (-1);
	ft_printf("\n%s (for architecture i386):\n", path);
	if (display_list_32(vault) == -1)
		return (-1);
	return (1);
}