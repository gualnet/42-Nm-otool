/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:21:21 by galy              #+#    #+#             */
/*   Updated: 2018/04/04 18:29:03 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	open_file(t_vault *vault, char *path)
{
	int			fd;
	
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_printf("\033[31mnm error :\n[%s] No such file or directory.\033[0m", path);
		return (-1);
	}
	if ((fstat(fd, &vault->f_stat)) < 0)
	{
		ft_printf("\033[31mnm error :\n[%s] stat gethering has failed\033[0m", path);
		return (-1);
	}
	if ((vault->fat_dump = (void *)mmap(NULL, vault->f_stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("\033[31mnm error :\n[$s] memory alloc has failed\033[0m", path);
		return (-1);
	}
	if (close(fd) != 0)
	{
		ft_printf("\033[33mnm warning :\n[$s] close not complete\033[0m", path);
	}
	exit (1);
	return (1);
}