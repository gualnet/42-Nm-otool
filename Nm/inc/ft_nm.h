/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:34:15 by galy              #+#    #+#             */
/*   Updated: 2018/02/22 11:55:39 by galy             ###   ########.fr       */
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

typedef struct		s_vault
{
	struct stat		f_stat;
	t_header		header;
}					t_vault;




//print_usage.c
void	print_usage(void);

#endif