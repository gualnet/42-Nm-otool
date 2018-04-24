/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:01:03 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:20:23 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** open the file and return a ptr
** on the file mapped in memory
*/

int	open_file(char *path, t_vault *vault)
{
	int			fd;
	
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_printf("\033[31mnm error :\n[%s] No such file or directory.\033[0m\n", path);
		return (-1);
	}
	if ((fstat(fd, &vault->f_stat)) < 0)
	{
		ft_printf("\033[31mnm error :\n[%s] stat gethering has failed\033[0m\n", path);
		return (-1);
	}
	if ((vault->f_dump = (void *)mmap(NULL, vault->f_stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("\033[31mnm error :\n[%s] File may be empty or was not recognized as a valid object file\033[0m\n", path);
		close(fd);
		return (-1);
	}
	if (close(fd) != 0)
	{
		ft_printf("\033[33mnm warning :\n[%s] close not complete\033[0m\n", path);
	}
	return (1);
}
