/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_object_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:59:14 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 17:00:55 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_object_path(t_vault *vault, struct ar_hdr *obj_hdr, char *path)
{
	char *o_name;

	ft_printf("%s", path);
	if (ft_strncmp(obj_hdr->ar_name, AR_EFMT1, 2) == 0)
	{
		o_name = offset_jumper(vault, obj_hdr, sizeof(struct ar_hdr));
		ft_printf("(");
		read_undelimited_str(o_name, ft_atoi(&obj_hdr->ar_name[3]));
		ft_printf("):\n");
	}
	else
	{
		o_name = (void*)obj_hdr->ar_name;
		ft_printf("(");
		read_undelimited_str(o_name, AR_NAME_SIZE);
		ft_printf("):\n");
	}
}
