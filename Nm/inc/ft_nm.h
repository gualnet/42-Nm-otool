/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:34:15 by galy              #+#    #+#             */
/*   Updated: 2018/03/13 15:10:21 by galy             ###   ########.fr       */
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
#include <mach-o/nlist.h>
#include "ft_printf.h"
#include "get_next_line.h"

#define	MH_32 struct mach_header
#define MH_64 struct mach_header_64

typedef struct				s_vault
{
	struct stat				f_stat;
	void					*f_dump;
	void					*f_dumptest;
	void					*header;
	int						file_nfo;
	// bit-flags ::::::swap endian:0x02-64bit:0x01-32bit
}							t_vault;

//print_usage.c
void	print_usage(void);

//vault_func.c
void	*init_vault(void);

//open_file.c
int		open_file(char *path, t_vault *vault);
int		check_magic_num(t_vault *vault);

//inter_cmds.c
void	inter_cmds(t_vault *vault);
void	inter_cmds_2(t_vault *vault);

//to_exit.c
void	to_exit(t_vault *vault);

//sort_alnum.c
void	sort_alnum(char **tab_symstr, unsigned int tab_len);

//dev_func.c
void print_symtab_command(void *sym_cmd);

#endif