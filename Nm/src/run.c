/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:09:26 by galy              #+#    #+#             */
/*   Updated: 2018/05/11 15:25:11 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		jump_params(char **argv, int argc, int i)
{
	while (argv[i][0] == '-')
	{
		i++;
		if (i == argc)
		{
			ft_printf("\033[31mnm error :\nError in parameters check\033[0m\n");
			return (-1);
		}
	}
	return (i);
}

int		little_if_forest(t_vault *vault, char *path, int i)
{
	int	print;
	int ret;

	print = 0;
	ret = 0;
	if (i > 2)
		print = 1;
	if ((vault->file_nfo & M_64B) != 0)
		ret = handle_64bits(vault, path, print);
	else if ((vault->file_nfo & M_32B) != 0)
		ret = handle_32bits(vault, path, print);
	else if ((vault->file_nfo & M_ARCH) != 0)
		ret = handle_arch(vault, path);
	else if ((vault->file_nfo & M_FAT) != 0)
		ret = handle_fat(vault, path);
	reset_tab_sym_meta(vault);
	delete_all_lst(vault);
	return (ret);
}

void	rl_err_msg(char *path)
{
	ft_printf("\033[31mnm error :\n[%s] was not recognized as a valid "
	"object file\033[0m\n", path);
}

int		running_loop(t_vault *vault, char **argv, int argc, int store)
{
	int		i;
	int		j;
	int		ret;

	i = 1;
	j = 0;
	while (i < argc)
	{
		ret = 0;
		if ((i = jump_params(argv, argc, i)) == -1)
			return (-1);
		vault = init_vault(vault);
		vault->option = store;
		if (open_file(argv[i], vault) != 1)
			ret = -1;
		if (ret != -1 && check_magic_num(vault) == -1)
		{
			rl_err_msg(argv[i]);
			ret = -1;
		}
		else if (ret != -1)
			little_if_forest(vault, argv[i], argc);
		i++;
	}
	return (1);
}

int		run(char **argv, int argc, t_vault *vault)
{
	int		store;

	if ((store = arg_pars(argv, argc)) == -1)
		return (-1);
	running_loop(vault, argv, argc, store);
	return (1);
}
