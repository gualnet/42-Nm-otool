/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/04/13 13:26:41 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int run(char **argv, int argc, t_vault *vault)
{
	char	*path;
	int		i;
	int		store;
	int		ret;
	
	i = 1;
	if ((store = arg_pars(argv, argc)) == -1)
		return (-1);
	while (i < argc)
	{
		while (argv[i][0] == '-')
		{
			i++;
			if (i == argc)
				return (-1);
		}
		path = argv[i];
		vault = init_vault(vault);
		vault->option = store;
		if (open_file(path, vault) != 1)
		{
			to_exit(vault);
			return (-1);
		}
		
		if (check_magic_num(vault) == -1)
		{
			ft_printf("\033[31mnm error :\nECHEC check magic num.\033[0m");
			return (-1);
		}
		
		if (argc > 2)
			return (-1); //???
		if ((vault->file_nfo & M_64B) != 0)
			ret = handle_64bits(vault, path, 1);
		else if ((vault->file_nfo & M_32B) != 0)
			ret = handle_32bits(vault, path);
		else if ((vault->file_nfo & M_ARCH) != 0)
			ret = handle_arch(vault, path);
		else if ((vault->file_nfo & M_FAT) != 0)
			ret = handle_fat(vault, path);
		// if (ret != 1)
		// 	return (-1);
		reset_tab_sym_meta(vault);
		delete_all_lst(vault);		
		i++;
	}
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
		return (EXIT_FAILURE);
	}
	if (run(argv, argc, vault) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
