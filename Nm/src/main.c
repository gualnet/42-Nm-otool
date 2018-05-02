/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 14:03:08 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		main(int argc, char **argv)
{
	t_vault	*vault;
	char	*alt[2];

	vault = NULL;
	if (argc < 2)
	{
		alt[0] = "NULL";
		alt[1] = "./a.out";
		if (run(alt, 2, vault) == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (run(argv, argc, vault) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
