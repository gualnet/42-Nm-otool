/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/02/22 12:00:03 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** open the file and return a ptr
** on the file mapped in memory
*/
void	*open_file(char *path, t_vault *vault)
{
	int			fd;
	void		*f_buff;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_printf("\033[31mnm error :\n[%s] No such file or directory.\033[0m", path);
		return (NULL);
	}
	if ((fstat(fd, &vault->f_stat)) < 0)
	{
		ft_printf("\033[31mnm error :\n[$s] stat gethering has failed\033[0m", path);
		return (NULL);
	}
	if ((f_buff = mmap(NULL, vault->f_stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("\033[31mnm error :\n[$s] memory maping has failed\033[0m", path);
		return (NULL);
	}
	ft_printf("OPEN FILE OKKKKKKKKKK\n");
	return (f_buff);
}

// void	header_construct(void *f_buff)
// {

// }

int	main(int argc, char **argv)
{
	t_vault	vault;
	
	if (argc < 2)
	{
		print_usage();
		return (0);
	}
	// j'ouvre mon fichier
	if (open_file(argv[1], &vault) == NULL)
		return (EXIT_FAILURE);
	

	
	return (EXIT_SUCCESS);
}