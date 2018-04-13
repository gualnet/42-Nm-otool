/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:43:29 by galy              #+#    #+#             */
/*   Updated: 2018/04/13 13:26:21 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_64bits(t_vault *vault, char *path, int print)
{	
	if (inter_cmds(vault) == -1)
		return (-1);
	if (print)
		ft_printf("\n%s:\n", path);
	if (display_list(vault) == -1)
		return (-1);
	return (1);
}