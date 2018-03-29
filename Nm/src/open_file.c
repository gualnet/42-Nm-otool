/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 21:01:03 by galy              #+#    #+#             */
/*   Updated: 2018/03/29 19:33:39 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"



int Magic_32_64(t_vault *vault)
{
	// ft_printf("MH_MAGIC_64 [%x]\n", MH_MAGIC_64);
	unsigned int magic_num;
	char *test;
	int nok;

	nok = 0;
	magic_num = *(unsigned int *)vault->f_dump;
	test = vault->f_dump;
	// ft_printf("LAAAA %x/%d\n\n", ARMAG, ft_strncmp(ARMAG, test, SARMAG));
	if (magic_num == MH_MAGIC_64 || magic_num == MH_CIGAM_64)
	{
		// ft_printf("==> struct 64bit\n");
		vault->file_nfo = M_64B;
	}
	else if (magic_num == MH_MAGIC || magic_num == MH_CIGAM)
	{
		// ft_printf("==> struct 32bit\n");
		vault->file_nfo = M_32B;
	}
	else if (ft_strncmp(ARMAG, test, SARMAG) == 0)
	{
		// ft_printf("==> struct arch\n");
		vault->file_nfo = M_ARCH;
	}
	else
		nok = 1;
	if (magic_num == MH_CIGAM || magic_num == MH_CIGAM_64)
	{
		// ft_printf("==> struct swap endian\n");
		vault->file_nfo += M_SWAP_ENDIAN;
	}
	if (nok == 1)
		return (-1);
	return (1);
}

// int change_endianness(int value)
// {
//     int result;

// 	result = 0;
//     result |= (value & 0x000000FF) << 24;
//     result |= (value & 0x0000FF00) << 8;
//     result |= (value & 0x00FF0000) >> 8;
//     result |= (value & 0xFF000000) >> 24;
//     return result;
// }

// int dump_swap_endianess(t_vault *vault)
// {
// 	ft_printf("\nCALL SWAPER\n");
// 	unsigned long long	i;
// 	void 				*ptr;
// 	void 				*ptr2;
// 	unsigned int		res;


// 	i = 0;
// 	ptr = vault->f_dump;
// 	vault->f_dumptest = malloc(sizeof(vault->f_stat.st_size));
// 	ptr2 = vault->f_dumptest;
// 	ft_printf("[%p]-->	%x\n", vault->f_dump, *(int*)ptr);
// 	ft_printf("[%p]-->	%x\n", vault->f_dumptest, *(int*)ptr);
// 	ft_printf("000\n");
// 	while (i < vault->f_stat.st_size / sizeof(int))
// 	{
// 		// ft_printf("[%p]-->	%x\n", &ptr, ptr);
// 		ft_printf("001\n");
// 		res = change_endianness(*(int *)ptr);
// 		ft_printf("002\n");
// 		ft_memcpy(ptr2, &res, sizeof(int));
// 		ft_printf("003\n");
// 		// ft_printf("[%p]-->	%x\n\n", &ptr, ptr);
// 		i++;
// 	}
// 	// ptr = *(unsigned int*)vault->f_dump;
// 	ft_printf("[%p]-->	%x\n", &ptr, &ptr);
// 	exit(0);
// 	return (1);
// }

/*
**	if the MAGIC is 64 bit
**	assigne a 64bit header to the dumped data
**	else the programme stop..
*/

int	check_magic_num(t_vault *vault)
{
	ft_printf("\nCALL CHECK MAGIC NUM\n");
	size_t header_size;
	
	header_size = -1;
	if ((Magic_32_64(vault)) == -1)
		return (-1);
	if (vault->file_nfo == 0x01 || vault->file_nfo == 0x05)
		header_size = sizeof(struct mach_header);
	else if (vault->file_nfo == 0x02 || vault->file_nfo == 0x06)
		header_size = sizeof(struct mach_header_64);
	else
		return (1);
	if ((vault->header = malloc(header_size)) == NULL)
		return (-1);
	ft_memcpy(vault->header, vault->f_dump, header_size);
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
	if ((vault->f_dump = (void *)mmap(NULL, vault->f_stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("\033[31mnm error :\n[$s] memory maping has failed\033[0m", path);
		return (-1);
	}
	// ft_printf("OPEN FILE OK vault->f_dump[%p]\n", vault->f_dump);
	if (close(fd) != 0)
	{
		ft_printf("\033[33mnm warning :\n[$s] close not complete\033[0m", path);
	}
	return (1);
}
