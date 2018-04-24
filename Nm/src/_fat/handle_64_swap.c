/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:43:29 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:31:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_64_swap(t_vault *vault, char *path, int print)
{	
	if (iter_cmds(vault) == -1)
		return (-1);
	if (print)
		ft_printf("\n%s:\n", path);
	if (display_list_64_swap(vault) == -1)
		return (-1);
	reset_tab_sym_meta(vault);
	delete_all_lst(vault);
	return (1);
}
