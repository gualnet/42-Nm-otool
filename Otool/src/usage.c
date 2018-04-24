/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:31:40 by galy              #+#    #+#             */
/*   Updated: 2018/04/24 18:39:28 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_usage(void)
{
	ft_putstr("USAGE: nm [options] <input files>\n");
	ft_putstr("\nOPTIONS:\n\n");
	ft_putstr("\t-t\tDisplay the contents of the (__TEXT,__text) section.  With the  -v\n \
	\tflag,  this disassembles the text.  With the -V flag, it also sym-\n \
	\tbolically disassembles the operands.\n");
}
