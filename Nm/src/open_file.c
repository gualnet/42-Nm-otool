/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:01:03 by galy              #+#    #+#             */
/*   Updated: 2018/02/23 21:28:39 by galy             ###   ########.fr       */
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
	// ft_memcpy((void*)(&vault->header_64), vault->f_buff, sizeof(t_header));
	unsigned int magic_num;

	magic_num = *(unsigned int *)vault->f_buff;

	ft_printf("magic number [%x] - ", magic_num);
	
	if (magic_num == MH_MAGIC_64)
		ft_printf("==> struct 64bit big endian\n");
	else if (magic_num == MH_CIGAM_64)
		ft_printf("==> struct 64bit small endian\n");
	else
	{
		ft_printf("this file is not encoded for 64bits arch.\n");
		to_exit(vault);
	}
	vault->header_64 = vault->f_buff;
	return (1);	
}

/*
** open the file and return a ptr
** on the file mapped in memory
*/

int	open_file(char *path, t_vault *vault)
{
	int			fd;
	ft_printf("vault->f_buff [%p]\n", vault->f_buff);

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
	ft_printf("OPEN FILE OKKKKKKKKKK [%p]\n", vault->f_buff);
	if (close(fd) != 0)
	{
		ft_printf("\033[33mnm warning :\n[$s] close not complete\033[0m", path);
	}
	ft_printf("vault->f_buff [%p]\n", vault->f_buff);
	return (1);
}
