/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:44:29 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:33:01 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_usage(void)
{
	ft_putstr("USAGE: nm [options] <input files>\n");
	ft_putstr("\nOPTIONS:\n\n");
	ft_putstr("\t-p     Don't sort; display in symbol-table order.\n");
	ft_putstr("\t-r     Sort in reverse order.\n");
	ft_putstr("\n");
}
