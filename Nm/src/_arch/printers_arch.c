/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_arch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:29:31 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 19:32:02 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_offset(t_vault *vault, void *ptr)
{
	void	*start;

	if (vault->ar_dump != NULL)
		start = (void*)vault->ar_dump;
	else
		start = (void*)vault->f_dump;
	ft_printf("\n\033[36moffset[%x]\033[00m\n", ptr - start, ptr - start);
}

void	print_object_path(t_vault *vault, struct ar_hdr *obj_hdr, \
char *path, char hdr_ext)
{
	char *o_name;

	if (hdr_ext == 1)
	{
		o_name = offset_jumper(vault, obj_hdr, sizeof(struct ar_hdr));
		ft_printf("\n%s", path);
		ft_printf("(");
		read_undelimited_str(o_name, ft_atoi(&obj_hdr->ar_name[3]));
		ft_printf("):\n");
	}
	else
	{
		o_name = (void*)obj_hdr->ar_name;
		ft_printf("%s", path);
		ft_printf("(");
		read_undelimited_str(o_name, AR_NAME_SIZE);
		ft_printf("):\n");
	}
}
