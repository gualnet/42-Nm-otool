/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 13:59:25 by galy              #+#    #+#             */
/*   Updated: 2018/03/14 18:39:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void sort_alnum(t_vault *vault, unsigned int tab_len)
{
	unsigned int	i;
	int	cmp_res;
	void *tmp;


	uint j = 0;
	i = 0;
	cmp_res = 0;
	while (i < tab_len - 1)
	{
		cmp_res = ft_strcmp(vault->tab_sym_meta[i]->name, vault->tab_sym_meta[i + 1]->name);
		// ft_printf("cmp %s / %s => %d\n", vault->tab_sym_meta[i]->name, vault->tab_sym_meta[i+1]->name, cmp_res);
		if (cmp_res > 0)// alpha sort
		{
			tmp = vault->tab_sym_meta[i + 1];
			vault->tab_sym_meta[i + 1] = vault->tab_sym_meta[i];
			vault->tab_sym_meta[i] = tmp;
			tmp = NULL;
			// ft_printf("%s / %s => %d change\n", vault->tab_sym_meta[i]->name, vault->tab_sym_meta[i+1]->name, cmp_res);
			i = 0;
			j = 0;
		}
		// if (cmp_res < 0)// sort alpha invert > option -r
		// {
		// 	tmp = vault->tab_sym_meta[i + 1];
		// 	vault->tab_sym_meta[i + 1] = vault->tab_sym_meta[i];
		// 	vault->tab_sym_meta[i] = tmp;
		// 	tmp = NULL;
		// 	ft_printf("%s / %s => %d change\n", vault->tab_sym_meta[i]->name, vault->tab_sym_meta[i+1]->name, cmp_res);
		// 	i = 0;
		// 	j = 0;
		// }
		else
			// ft_printf("%s / %s => %d\n", vault->tab_sym_meta[i]->name, vault->tab_sym_meta[i+1]->name, cmp_res);
		i++;
	}
}
