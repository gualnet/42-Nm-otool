/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:31:40 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 10:20:41 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_usage(void)
{
	ft_putstr("USAGE: nm [options] <input files>\n");
	ft_putstr("\nOPTIONS:\n\n");
	ft_putstr("\t\033[37;1m-t\033[0m\tDisplay the contents of the "
	"(__TEXT,__text) section.\n");
}
