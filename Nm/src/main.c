/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/03/10 13:49:22 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int run(char **argv, t_vault *vault)
{
	// j'ouvre mon fichier
	if (open_file(argv[1], vault) != 1)
		to_exit(vault);
	
	// check magic number
	check_magic_num(vault);

	// load commands
	inter_cmds(vault);

	return (1);
}

int	main(int argc, char **argv)
{
	t_vault	*vault;

	vault = init_vault();
	if (argc < 2)
	{
		print_usage();
		return (0);
	}
	
	run(argv, vault);

	return (EXIT_SUCCESS);
}
