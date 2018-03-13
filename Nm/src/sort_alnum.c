/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 13:59:25 by galy              #+#    #+#             */
/*   Updated: 2018/03/13 15:33:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	sort_alnum(char **tab_symstr, unsigned int tab_len)
{
	unsigned int	i;
	int	cmp_res;
	void *tmp;


	uint j = 0;
	i = 0;
	while (i < tab_len - 1)
	{
		cmp_res = 0;
		cmp_res = ft_strcmp(tab_symstr[i], tab_symstr[i + 1]);
		if (cmp_res > 0)// alpha sort
		{
			tmp = tab_symstr[i + 1];
			tab_symstr[i + 1] = tab_symstr[i];
			tab_symstr[i] = tmp;
			tmp = NULL;
			// ft_printf("%s / %s => %d change\n", tab_symstr[i], tab_symstr[i+1], cmp_res);
			i = 0;
			j = 0;
		}
		// if (cmp_res < 0)// sort alpha invert > option -r
		// {
		// 	tmp = tab_symstr[i + 1];
		// 	tab_symstr[i + 1] = tab_symstr[i];
		// 	tab_symstr[i] = tmp;
		// 	tmp = NULL;
		// 	ft_printf("%s / %s => %d change\n", tab_symstr[i], tab_symstr[i+1], cmp_res);
		// 	i = 0;
		// 	j = 0;
		// }
		else
			// ft_printf("%s / %s => %d\n", tab_symstr[i], tab_symstr[i+1], cmp_res);
		i++;
	}
	j = 0;
	while (j < tab_len) // pour test
	{
		ft_printf("->%s<-\n", tab_symstr[j]);
		j++;
	}
}