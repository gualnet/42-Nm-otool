/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:34:15 by galy              #+#    #+#             */
/*   Updated: 2018/02/23 21:26:48 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include "ft_printf.h"
#include "get_next_line.h"


typedef struct		s_header
{
	unsigned int	magic;			// uint32 :magic
	int				cpu_type;		// int32 :cputype
	int				cpu_subtype;	// int32 :cpusubtype
	unsigned int	file_type;		// uint32 :filetype
	unsigned int	ncmds;			// uint32 :ncmds
	unsigned int	sizeofcmds;		// uint32 :sizeofcmds
	unsigned int	flags;			// uint32 :flags
}					t_header;

typedef struct				s_vault
{
	struct stat				f_stat;
	void					*f_buff;
	struct mach_header_64	*header_64;
}							t_vault;




//print_usage.c
void	print_usage(void);

//vault_func.c
void	*init_vault(void);

//open_file.c
int		open_file(char *path, t_vault *vault);
int		check_magic_num(t_vault *vault);


//to_exit.c
void	to_exit(t_vault *vault);

#endif