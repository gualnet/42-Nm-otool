/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:37:50 by galy              #+#    #+#             */
/*   Updated: 2018/04/05 10:16:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL
# define FT_OTOOL

/*
**	headers
*/
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <ar.h>

#include "ft_printf.h"


/*
**	defines
*/
/*
**	Defines for file_nfo
**	M_32B			- 32 bits file
**	M_64B			- 64 bits file
**	M_SWAP_ENDIAN	- 
**	M_ARCH			- archive file
**	M_FAT			- fat file
*/
#define M_32B				0x01
#define M_64B				0x02
#define M_SWAP_ENDIAN		0x04
#define M_ARCH				0x08
#define M_FAT				0x10


/*
**	option
*/

typedef struct				s_vault
{
	struct stat				f_stat;
	void					*fat_dump;
	void					*ar_dump;
	void					*o_dump;
	int						file_nfo;
	int						option;
	// void					*header;
	// t_lc_lnk				*lc_lst;
	// t_sym_meta				**tab_sym_meta;	
	// unsigned int			nsyms; //nbr of symbols
}							t_vault;


/*
**	Func
*/

//open_file.c
int		open_file(t_vault *vault, char *path);

//usage.c
void	print_usage(void);

//check_magic.c
int		check_magic_num(t_vault *vault);

//vault_init.c
void	*init_vault(t_vault *vault);





#endif