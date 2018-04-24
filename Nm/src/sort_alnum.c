/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 13:59:25 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:22:37 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void sort_alnum_(t_vault *vault, unsigned int tab_len)
{
	unsigned int	i;
	unsigned int	j;
	int				cmp_res;
	void			*tmp;

	i = 0;
	j = 0;
	cmp_res = 0;
	while (i < tab_len - 1)
	{
		cmp_res = ft_strcmp(vault->tab_sym_meta[i]->name, vault->tab_sym_meta[i + 1]->name);
		if (cmp_res > 0)
		{
			tmp = vault->tab_sym_meta[i + 1];
			vault->tab_sym_meta[i + 1] = vault->tab_sym_meta[i];
			vault->tab_sym_meta[i] = tmp;
			tmp = NULL;
			i = 0;
			j = 0;
		}
		else
		{
			// a tester	
		}
		i++;
	}
}

void sort_alnum_reverse(t_vault *vault, unsigned int tab_len)
{
	unsigned int	i;
	unsigned int	j;
	int				cmp_res;
	void			*tmp;

	i = 0;
	j = 0;
	cmp_res = 0;
	while (i < tab_len - 1)
	{
		cmp_res = ft_strcmp(vault->tab_sym_meta[i]->name, vault->tab_sym_meta[i + 1]->name);
		if (cmp_res < 0)
		{
			tmp = vault->tab_sym_meta[i + 1];
			vault->tab_sym_meta[i + 1] = vault->tab_sym_meta[i];
			vault->tab_sym_meta[i] = tmp;
			tmp = NULL;
			i = 0;
			j = 0;
		}
		else
		{
			// a tester
		}
		i++;
	}
}

void sort_alnum(t_vault *vault, unsigned int tab_len)
{
	if ((vault->option & OPT_REVERSE) != 0)
		sort_alnum_reverse(vault, tab_len);
	else if ((vault->option & OPT_NOSORT) == 0)
		sort_alnum_(vault, tab_len);
}
