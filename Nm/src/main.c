/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/03/22 12:04:04 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int run(char **argv, t_vault *vault)
{
	// j'ouvre mon fichier
	if (open_file(argv[1], vault) != 1)
		to_exit(vault);
	
	// check magic number
	if (check_magic_num(vault) == -1)
	{
		ft_printf("\033[31mnm error :\nECHEC check magic num.\033[0m");
		return (-1);
	}
		
	// load commands
	if ((vault->file_nfo & M_64B) != 0)
	{
		inter_cmds(vault);
	}
	else
		exit(0);

	display_list(vault);
	ft_printf("\nEND\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_vault	*vault;

	vault = init_vault();
	if (argc < 2)
	{
		//check de a.out si pas d'args.
		print_usage();
		return (0);
	}
	
	run(argv, vault);

	return (EXIT_SUCCESS);
}
