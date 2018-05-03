/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset_jumper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:22:16 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 14:38:08 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*offset_jumper(t_vault *vault, void *ptr, long jumpsize)
{
	void	*start_adr;
	void	*max_adr;
	void	*new_adr;

	start_adr = (vault->ar_dump != NULL) ? vault->ar_dump : vault->f_dump;
	new_adr = NULL;
	max_adr = (void*)start_adr + vault->f_stat.st_size;
	new_adr = (void*)ptr + jumpsize;
	if (new_adr == NULL || new_adr < vault->ar_dump || new_adr > max_adr)
	{
		ft_printf("\033[31motool error:\n"
		"\tTruncated or malformed object\n\033[0m");
		return (NULL);
	}
	return (new_adr);
}

void	*offset_jumper_neg(t_vault *vault, void *ptr, long jumpsize)
{
	void	*start_adr;
	void	*max_adr;
	void	*new_adr;

	start_adr = (vault->ar_dump != NULL) ? vault->ar_dump : vault->f_dump;
	new_adr = NULL;
	max_adr = (void*)start_adr + vault->f_stat.st_size;
	new_adr = (void*)ptr + jumpsize;
	if (new_adr == NULL || new_adr < vault->ar_dump || new_adr >= max_adr)
	{
		ft_printf("\033[31motool error:\n"
		"\tTruncated or malformed object\n\033[0m");
		return (NULL);
	}
	return (new_adr);
}
