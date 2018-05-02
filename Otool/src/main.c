/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:06:25 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 10:28:56 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		get_option(char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (i == 1 && ft_strcmp(argv[1], "-t") != 0)
		{
			print_usage();
			return (-1);
		}
		if (i != 1 && argv[i][0] != '-')
			break ;
		i++;
	}
	if (argc == 2)
	{
		print_usage();
		return (-1);
	}
	return (i);
}

int		type_router(t_vault *vault, char *path)
{
	int	ret;

	ret = 0;
	if ((vault->file_nfo & M_64B) != 0)
		ret = handle_64(vault);
	else if (ret != -1 && (vault->file_nfo & M_32B) != 0)
		ret = handle_32(vault);
	else if (ret != -1 && (vault->file_nfo & M_FAT) != 0)
		ret = handle_fat(vault, path);
	else if (ret != -1 && (vault->file_nfo & M_ARCH) != 0)
		ret = handle_arch(vault, path);
	else
		return (-1);
	return (1);
}

int		inner_run(t_vault *vault, char **argv, int i)
{
	if ((vault->file_nfo & M_ARCH) == M_ARCH)
		ft_printf("Archive : %s\n", argv[i]);
	else if (!((vault->file_nfo & M_FAT) == M_FAT))
		ft_printf("%s:\n", argv[i]);
	if (type_router(vault, argv[i]) == -1)
		return (-1);
	if (re_init_vault(vault) == NULL)
		return (-1);
	return (0);
}

int		run(t_vault *vault, char **argv, int argc)
{
	int i;
	int ret;

	if ((vault = init_vault(vault)) == NULL)
		return (-1);
	if ((i = get_option(argv, argc)) == -1)
		return (-1);
	while (i < argc)
	{
		ret = 0;
		if ((open_file(vault, argv[i])) == -1)
			return (-1);
		if (ret != -1 && check_magic_num(vault) == -1)
		{
			ft_printf("\033[31motool error :\n[%s] ", argv[i]);
			ft_printf("was not recognized as a valid object file\033[0m\n");
			ret = -1;
		}
		else if (inner_run(vault, argv, i) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_vault *vault;

	vault = NULL;
	if (argc < 2)
		print_usage();
	if (run(vault, argv, argc) == -1)
		return (-1);
	return (0);
}
