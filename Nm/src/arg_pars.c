/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:12:13 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:32:57 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		store_arg(char *arg)
{
	int store;

	store = 0;
	if (ft_strcmp("-r", arg) == 0)
		store += OPT_REVERSE;
	if (ft_strcmp("-p", arg) == 0)
		store += OPT_NOSORT;
	return (store);
}

int		arg_pars(char **argv, int argc)
{
	int	i;
	int	after;
	int	store;

	i = 1;
	after = 0;
	store = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-' && after == 0)
			after = 1;
		else if (argv[i][0] == '-' && after == 1)
		{
			print_usage();
			return (-1);
		}
		if (argv[i][0] == '-')
			store += store_arg(argv[i]);
		i++;
	}
	return (store);
}
