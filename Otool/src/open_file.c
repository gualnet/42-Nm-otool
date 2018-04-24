/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:21:21 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:37:28 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		replace_map(t_vault *vault)
{
	void	*tmp;
	
	tmp = vault->fat_dump;
	if ((vault->fat_dump = malloc(vault->f_stat.st_size)) == NULL)
		return (-1);
	if (ft_memcpy(vault->fat_dump, tmp, vault->f_stat.st_size) == NULL)
		return (-1);
	if (munmap(tmp, vault->f_stat.st_size) == -1)
		return (-1);
	return (1);
}

int		open_file(t_vault *vault, char *path)
{
	int			fd;
	
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_printf("\033[31motool error :\n[%s] No such file or directory.\033[0m", path);
		return (-1);
	}
	if ((fstat(fd, &vault->f_stat)) < 0)
	{
		ft_printf("\033[31motool error :\n[%s] stat gethering has failed\033[0m", path);
		return (-1);
	}
	if ((vault->fat_dump = (void *)mmap(NULL, vault->f_stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("\033[31motool error :\n[%s] ", path);
		ft_printf("File may be empty or was not recognized as a valid object file\
		\033[0m\n");
		return (-1);
	}
	if (close(fd) != 0)
	{
		ft_printf("\033[33motool warning :\n[%s] close not complete\033[0m", path);
	}
	return (replace_map(vault));
}
