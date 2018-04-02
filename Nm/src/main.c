/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/04/02 18:44:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int run(char **argv, int argc, t_vault *vault)
{
	char	*path;
	int		i;

	i = 1;
	while (i < argc)
	{
		path = argv[i];
		vault = init_vault(vault);
		// j'ouvre mon fichier
		if (open_file(path, vault) != 1)
			to_exit(vault);
		// check magic number
		if (check_magic_num(vault) == -1)
		{
			ft_printf("\033[31mnm error :\nECHEC check magic num.\033[0m");
			return (-1);
		}
		
		
		if (argc > 2)
			ft_printf("\n%s:\n", path);
		// load commands
		if ((vault->file_nfo & M_64B) != 0)
		{
			handle_64bits(vault);
		}
		else if ((vault->file_nfo & M_ARCH) != 0)
		{
			handle_arch(vault, path);
		}
		else if ((vault->file_nfo & M_32B) != 0)
		{
			handle_32bits(vault);
		}
		else
			exit(0);
		reset_tab_sym_meta(vault);
		i++;
	}
	

	// ft_printf("\nEND\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_vault	*vault;

	vault = NULL;
	if (argc < 2)
	{
		//check de a.out si pas d'args.
		print_usage();
		return (0);
	}
	
	run(argv, argc, vault);

	return (EXIT_SUCCESS);
}
