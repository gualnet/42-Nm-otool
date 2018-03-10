/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:34:15 by galy              #+#    #+#             */
/*   Updated: 2018/03/10 13:16:24 by galy             ###   ########.fr       */
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


// enum						e_header_type
// {
// 	int 32_little,
// 	int 32_big,
// 	int 64_little,
// 	int 64_big,
// };

union						u_header
{
	struct mach_header		_32;
	struct mach_header_64	_64;
	// enum e_header_type		type;
};

typedef struct				s_vault
{
	struct stat				f_stat;
	void					*f_buff;
	union u_header			*header;
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

#endif