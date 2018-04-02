/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:34:15 by galy              #+#    #+#             */
/*   Updated: 2018/04/02 18:45:38 by galy             ###   ########.fr       */
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
#include <mach-o/fat.h>
#include <ar.h>
#include "ft_printf.h"
#include "get_next_line.h"

/*
**	Defines for file_nfo
**	M_32B			- 32 bits
**	M_64B			- 64 bits
**	M_SWAP_ENDIAN	-
**	M_ARCH			- archive 
*/
#define M_32B				0x01
#define M_64B				0x02
#define M_SWAP_ENDIAN		0x04
#define M_ARCH				0x08
#define LONG_NAME_SIZE		20
#define AR_NAME_SIZE		16

typedef struct				s_sym_meta
{
	char					*name;	// symbol name
	char					n_type;	// type flag
	char					n_sect; // section number
	unsigned long			n_value;
}							t_sym_meta;

typedef struct				s_sect_lnk_32
{
	struct section			*sect_32;
	void					*next;
}							t_sect_lnk_32;

typedef struct				s_sect_lnk
{
	struct section_64		*sect;
	void					*next;
}							t_sect_lnk;

typedef struct				s_lc_lnk
{
	struct load_command		*lc;
	union
	{
		t_sect_lnk_32		*lnk_32;
		t_sect_lnk			*lnk_64;
	}						sect_lst;
	// t_sect_lnk				*sect_lst;
	void					*next;
}							t_lc_lnk;

typedef struct				s_arch_info
{
	struct ar_hdr			*off_symtab_hdr;
	void					*off_symbol_tab;
	void					*off_symstr_tab;
	unsigned int			nbr_obj;
	
}							t_arch_info;

typedef struct				s_vault
{
	struct stat				f_stat;
	void					*ar_dump;
	void					*f_dump;
	void					*header;
	t_lc_lnk				*lc_lst;
	t_sym_meta				**tab_sym_meta;	
	int						file_nfo;
	unsigned int			nsyms; //nbr of symbols
	// bit-flags ::::::swap endian:0x02-64bit:0x01-32bit
}							t_vault;

//print_usage.c
void	print_usage(void);

//vault_func.c
void	*init_vault(t_vault *vault);
void	reset_tab_sym_meta(t_vault *vault);

//open_file.c
int		open_file(char *path, t_vault *vault);
int		check_magic_num(t_vault *vault);

//inter_cmds.c
void	inter_cmds(t_vault *vault);

//to_exit.c
void	to_exit(t_vault *vault);

//sort_alnum.c
void	sort_alnum(t_vault *vault, unsigned int tab_len);

//display.c
void	display_list(t_vault *vault);

//lst_func.c
t_lc_lnk	*add_new_lclink(t_vault *vault, void *adr);
t_sect_lnk	*add_new_sectlnk(t_lc_lnk *lc_lnk, void *adr);
int			delete_all_lst(t_vault *vault);

//lst_func_32.c
t_lc_lnk	*add_new_lclink_32(t_vault *vault, void *adr);
t_sect_lnk_32	*add_new_sectlnk_32(t_lc_lnk *lc_lnk, void *adr);
int			delete_all_lst_32(t_vault *vault);

//check_sym_sect.c
char	print_sym_sect(t_vault *vault, unsigned int i);

//handle_arch.c
void	handle_arch(t_vault *vault, char *path);
void	print_offset(t_vault *vault, void *ptr);

// read_undelimited_str.c
void	read_undelimited_str(char *ptr, size_t size);

//offset_jumper.c
void	*offset_jumper(t_vault *vault, void *ptr, long jumpsize);

//check_magic.c
int	check_magic_num(t_vault *vault);

//handle_64.c
void	handle_64bits(t_vault *vault);

//handle_32.c
void	handle_32bits(t_vault *vault);
void	inter_cmds_32(t_vault *vault);

//dev_func.c
void print_symtab_command(void *sym_cmd);
// void	print_lc_lst(t_vault *vault);
void	display_list_32(t_vault *vault);
char	print_sym_sect_32(t_vault *vault, unsigned int i);


#endif