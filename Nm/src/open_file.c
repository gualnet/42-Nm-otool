/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:01:03 by galy              #+#    #+#             */
/*   Updated: 2018/05/03 15:04:21 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	close_my_ffd(int fd, char *path)
{
	if (close(fd) != 0)
		ft_printf(TXT_YELLOW"nm warning :\n[%s] file descriptor close not "
		"complete"TXT_0"\n", path);
}

/*
** open the file and return a ptr
** on the file mapped in memory
*/

int		open_file(char *path, t_vault *vault)
{
	int			fd;

	if ((fd = open(path, O_RDONLY | O_NONBLOCK)) == -1)
	{
		ft_printf(TXT_RED"error :\n[%s] No such file or directory."
		TXT_0"\n", path);
		return (-1);
	}
	if ((fstat(fd, &vault->f_stat)) < 0)
	{
		ft_printf(TXT_RED"error :\n[%s] stat gethering has failed"
		TXT_0"\n", path);
		return (-1);
	}
	if ((vault->f_dump = (void *)mmap(NULL, vault->f_stat.st_size, \
	PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf(TXT_RED"error :\n[%s] File may be empty or was not "
		"recognized as a valid object file"TXT_0"\n", path);
		close(fd);
		return (-1);
	}
	close_my_ffd(fd, path);
	return (1);
}
