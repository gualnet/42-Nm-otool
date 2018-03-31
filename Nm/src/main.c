/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/03/31 04:13:46 by galy             ###   ########.fr       */
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
		// j'ouvre mon fichier
		if (open_file(argv[i], vault) != 1)
			to_exit(vault);
		// check magic number
		if (check_magic_num(vault) == -1)
		{
			ft_printf("\033[31mnm error :\nECHEC check magic num.\033[0m");
			return (-1);
		}
		
		path = argv[i];
		if (argc > 2)
			ft_printf("\n%s:\n", path);
		// load commands
		if ((vault->file_nfo & M_64B) != 0)
		{
			inter_cmds(vault);
			display_list(vault);
		}
		else if ((vault->file_nfo & M_ARCH) != 0)
		{
			
			handle_arch(vault, path);
			// ft_printf("\nEXIT - main.c line 36\n");
			// exit(0);
		}
		else
			exit(0);
		i++;
	}
	

	// ft_printf("\nEND\n");
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
	
	run(argv, argc, vault);

	return (EXIT_SUCCESS);
}
