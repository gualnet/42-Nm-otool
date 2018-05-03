/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:37:50 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 10:40:13 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>
# include "ft_printf.h"

# if defined (__x86_64__)
#  define CUR_CPU "x86_64"
# endif
# define M_32B				0x01
# define M_64B				0x02
# define M_SWAP_ENDIAN		0x04
# define M_ARCH				0x08
# define M_FAT				0x10
# define AR_NAME_SIZE		16

/*
**	Struct
*/
typedef struct				s_arch_info
{
	struct ar_hdr			*symtab_hdr;
	void					*off_symbol_tab;
	void					*off_symstr_tab;
	unsigned int			nbr_obj;
}							t_arch_info;

typedef struct				s_vault
{
	struct stat				f_stat;
	void					*fat_dump;
	void					*ar_dump;
	void					*o_dump;
	void					*sect_hdr;
	void					*sect;
	int						file_nfo;
	int						option;
}							t_vault;

/*
**	Func
*/
void						print_usage(void);
void						*init_vault(t_vault *vault);
void						*re_init_vault(t_vault *vault);
void						*offset_jumper(t_vault *vault, void *ptr, \
							long jumpsize);
void						read_undelimited_str(char *ptr, size_t size);
void						swap_info_data(struct fat_arch *info);
void						swap_header_data(struct mach_header	*header);
void						print_offset(t_vault *vault, void *ptr);
void						print_object_path(t_vault *vault, \
							struct ar_hdr *obj_hdr, char *path);
long						swap_long_endian(long value);
char						*extract_file_name(char *path);
int							open_file(t_vault *vault, char *path);
int							check_magic_num(t_vault *vault);
int							handle_64(t_vault *vault);
int							handle_32(t_vault *vault);
int							handle_fat(t_vault *vault, char *path);
int							handle_arch(t_vault *vault, char *path);
int							print_sect_dump_64(t_vault *vault);
int							print_sect_dump_32(t_vault *vault);
int							jump_obj_hdr(t_vault *vault, t_arch_info *arch, \
							char *path);
int							jump_to_exec(t_vault *vault, \
							struct fat_arch *info);
int							swap_endian(int value);
int							handle_32_fat(t_vault *vault, char *path);
int							handle_ppc_fat(t_vault *vault, char *path);
int							print_sect_dump_ppc(t_vault *vault);
int							get_fat_cpu_type_else(t_vault *vault, \
							unsigned long nbr_arch, char *path);

#endif
