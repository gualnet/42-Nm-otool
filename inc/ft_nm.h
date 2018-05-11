/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:34:15 by galy              #+#    #+#             */
/*   Updated: 2018/05/10 19:21:09 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "ft_txt_color.h"

/*
**	OPTIONS
**	OPT_REVERSE "-r"
**	OPT_NOSORT "-p"
*/
# define OPT_REVERSE		0x01
# define OPT_NOSORT			0x02

/*
**	Defines for file_nfo
**	M_32B			- 32 bits file
**	M_64B			- 64 bits file
**	M_SWAP_ENDIAN	-
**	M_ARCH			- archive file
**	M_FAT			- fat file
*/
# define M_32B				0x01
# define M_64B				0x02
# define M_SWAP_ENDIAN		0x04
# define M_ARCH				0x08
# define M_FAT				0x10

# define AR_NAME_SIZE		16

# if defined (__x86_64__)
#  define CUR_CPU "x86_64"
# endif

typedef struct				s_sym_meta
{
	char					*name;
	char					n_type;
	char					n_sect;
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
	union					u_sect_lst
	{
		t_sect_lnk_32		*lnk_32;
		t_sect_lnk			*lnk_64;
	}						sect_lst;
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
	void					*strtab;
	int						file_nfo;
	unsigned int			nsyms;
	unsigned long			nbr_sect;
	int						option;
}							t_vault;

void						print_usage(void);
void						*init_vault(t_vault *vault);
void						reset_tab_sym_meta(t_vault *vault);
int							open_file(char *path, t_vault *vault);
int							check_magic_num(t_vault *vault);
int							iter_cmds(t_vault *vault);
size_t						ft_strlen_cap(t_vault *vault, const char *s);
int							to_exit(t_vault *vault);
void						sort_alnum(t_vault *vault, unsigned int tab_len);
int							display_list(t_vault *vault);
t_lc_lnk					*add_new_lclink(t_vault *vault, void *adr);
t_sect_lnk					*add_new_sectlnk(t_lc_lnk *lc_lnk, void *adr);
int							delete_all_lst(t_vault *vault);
t_lc_lnk					*add_new_lclink_32(t_vault *vault, void *adr);
t_sect_lnk_32				*add_new_sectlnk_32(t_lc_lnk *lc_lnk, void *adr);
int							delete_all_lst_32(t_vault *vault);
char						print_sym_sect(t_vault *vault, unsigned int i);
void						print_offset(t_vault *vault, void *ptr);
void						read_undelimited_str(char *ptr, size_t size);
void						*offset_jumper(t_vault *vault, void *ptr, \
							long jumpsize);
int							check_magic_num(t_vault *vault);
int							handle_fat(t_vault *vault, char *path);
int							handle_arch(t_vault *vault, char *path);
int							handle_32bits(t_vault *vault, char *path, \
							int print);
int							handle_64bits(t_vault *vault, char *path, \
							int print);
int							handle_32_in_fat(t_vault *vault, char *path);
int							handle_ppc_in_fat(t_vault *vault, char *path);
int							iter_cmds_ppc(t_vault *vault);
int							display_list_ppc(t_vault *vault);
char						print_sym_sect_ppc(t_vault *vault, unsigned int i);
int							handle_64_swap(t_vault *vault, char *path, \
							int print);
int							display_list_64_swap(t_vault *vault);
char						print_sym_sect_64_swap(t_vault *vault, \
							unsigned int i);
int							iter_cmds_32(t_vault *vault);
int							iter_cmds_ppc(t_vault *vault);
long						swap_endian(long value);
void						*get_indirection_name(t_vault *vault, \
							unsigned int i);
void						print_symtab_command(void *sym_cmd);
int							arg_pars(char **argv, int argc);
int							display_list_32(t_vault *vault);
char						print_sym_sect_32(t_vault *vault, unsigned int i);
int							run(char **argv, int argc, t_vault *vault);
size_t						ft_strlen_cap(t_vault *vault, const char *s);
int							jump_obj_hdr(t_vault *vault, t_arch_info *arch, \
							char *path);
void						print_object_path(t_vault *vault, \
							struct ar_hdr *obj_hdr, char *path, char hdr_ext);
void						free_useless_vault_components(t_vault *vault);

#endif
