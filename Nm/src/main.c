/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/02/23 21:31:30 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	main(int argc, char **argv)
{
	t_vault	*vault;

	vault = init_vault();
	if (argc < 2)
	{
		print_usage();
		return (0);
	}
	// j'ouvre mon fichier
	if (open_file(argv[1], vault) == 1)
		to_exit(vault);

	
	return (EXIT_SUCCESS);
}