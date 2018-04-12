/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:43:29 by galy              #+#    #+#             */
/*   Updated: 2018/04/11 18:23:33 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_64bits(t_vault *vault, char *path)
{	
	if (inter_cmds(vault) == -1)
		return (-1);
	ft_printf("\n%s:\n", path);
	if (display_list(vault) == -1)
		return (-1);
	return (1);
}