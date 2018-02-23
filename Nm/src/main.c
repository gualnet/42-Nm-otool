/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:32:02 by galy              #+#    #+#             */
/*   Updated: 2018/02/22 14:37:07 by galy             ###   ########.fr       */
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
	ft_printf("vault->f_buff [%p]\n", vault->f_buff);

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
	if ((vault->f_buff = (void *)mmap(NULL, vault->f_stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("\033[31mnm error :\n[$s] memory maping has failed\033[0m", path);
		return (NULL);
	}
	ft_printf("OPEN FILE OKKKKKKKKKK [%p]\n", vault->f_buff);
	if (close(fd) != 0)
	{
		ft_printf("\033[33mnm warning :\n[$s] close not complete\033[0m", path);
	}
	ft_printf("vault->f_buff [%p]\n", vault->f_buff);
	return (vault->f_buff);
}

void	header_construct(t_vault *vault)
{
	ft_memcpy((void*)(&vault->header), vault->f_buff, sizeof(t_header));
	ft_printf("test [%p]", vault->header.magic);
	if (vault->header.magic == MH_MAGIC_64)
		ft_printf("test : yes");
	else
		ft_printf("test : no");
}

void	*init_vault(void)
{
	t_vault *init;

	init = malloc(sizeof(t_vault));
	init->f_buff = NULL;
	return (init);

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
	// j'ouvre mon fichier
	if (open_file(argv[1], vault) == NULL)
		return (EXIT_FAILURE);
		
	header_construct(vault);

	
	return (EXIT_SUCCESS);
}