/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vault_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 20:59:32 by galy              #+#    #+#             */
/*   Updated: 2018/03/15 11:20:42 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*init_vault(void)
{
	t_vault *init;

	if ((init = malloc(sizeof(t_vault))) == NULL)
	{
		ft_printf("\033[31mnm (init.c - line 19) error :\nmalloc vault struct space FAILED\033[0m\n");
		to_exit(NULL);
	}
	init->f_dump = NULL;
	init->lc_lst = NULL;
	return (init);

}