/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 04:43:10 by galy              #+#    #+#             */
/*   Updated: 2018/04/17 12:37:18 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_32bits(t_vault *vault, char *path)
{
	if (iter_cmds_32(vault) == -1)
		return (-1);
	ft_printf("\n%s:\n", path);
	if (display_list_32(vault) == -1)
		return (-1);
	return (1);
}