/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:01:03 by galy              #+#    #+#             */
/*   Updated: 2018/03/10 11:46:56 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
**	if the MAGIC is 64 bit
**	assigne a 64bit header to the dumped data
**	else the programme stop..
*/

int	check_magic_num(t_vault *vault)
{
	ft_printf("\nCALL CHECK MAGIC NUM\n");
	// ft_memcpy((void*)(&vault->header_64), vault->f_buff, sizeof(t_header));
	unsigned int magic_num;

	magic_num = *(unsigned int *)vault->f_buff;
	ft_printf("magic number [%x] - ", magic_num);
	if (magic_num == MH_MAGIC_64 || magic_num == MH_CIGAM_64)
	{
		ft_printf("==> struct 64bit\n");
		vault->header = vault->f_buff;
	}
	else if (magic_num == MH_MAGIC || magic_num == MH_CIGAM)
	{
		ft_printf("==> struct 32bit\n");
		vault->header = vault->f_buff;
		// to_exit(vault);
	}
	else
	{
		ft_printf("\033[31mMAGIC NUM INVALID\033[0m\n");
		to_exit(vault);
	}
	return (1);	
}

/*
** open the file and return a ptr
** on the file mapped in memory
*/

int	open_file(char *path, t_vault *vault)
{
	int			fd;
	
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_printf("\033[31mnm error :\n[%s] No such file or directory.\033[0m", path);
		return (-1);
	}
	if ((fstat(fd, &vault->f_stat)) < 0)
	{
		ft_printf("\033[31mnm error :\n[$s] stat gethering has failed\033[0m", path);
		return (-1);
	}
	if ((vault->f_buff = (void *)mmap(NULL, vault->f_stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("\033[31mnm error :\n[$s] memory maping has failed\033[0m", path);
		return (-1);
	}
	ft_printf("OPEN FILE OK vault->f_buff[%p]\n", vault->f_buff);
	if (close(fd) != 0)
	{
		ft_printf("\033[33mnm warning :\n[$s] close not complete\033[0m", path);
	}
	return (1);
}
