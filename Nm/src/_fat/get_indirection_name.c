/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_indirection_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 10:24:41 by galy              #+#    #+#             */
/*   Updated: 2018/05/03 11:29:55 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*get_indirection_name(t_vault *vault, unsigned int i)
{
	void			*ptr;
	unsigned int	jump;

	jump = vault->tab_sym_meta[i]->n_value;
	ptr = offset_jumper(vault, vault->strtab, jump);
	return (ptr);
}
