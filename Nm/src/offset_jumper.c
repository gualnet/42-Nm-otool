/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset_jumper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:22:16 by galy              #+#    #+#             */
/*   Updated: 2018/04/04 15:50:49 by galy             ###   ########.fr       */
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
		ft_printf("\n\nERROR JUMPER_AR [%p][%x]\n\n", new_adr,\
		(void*)vault->ar_dump - new_adr);
		return (NULL);
	}
	// ft_printf("\033[36mjumped to [%p] - offset [%x]\033[0m\n"\
	// , new_adr, new_adr - start_adr);
	return (new_adr);
}

void	*offset_jumper_neg(t_vault *vault, void *ptr, long jumpsize)
{
	void	*start_adr;
	void	*max_adr;
	void	*new_adr;
	
	start_adr = (vault->ar_dump != NULL) ? vault->ar_dump : vault->f_dump;
	new_adr = NULL;
	// ft_printf("vault->f_stat.st_size [%p]\n", vault->f_stat.st_size);
	max_adr = (void*)start_adr + vault->f_stat.st_size;
	// ft_printf("max_adr [%p]\n", max_adr);

	new_adr = (void*)ptr + jumpsize;
	if (new_adr == NULL || new_adr < vault->ar_dump || new_adr > max_adr)
	{
		ft_printf("\n\nERROR JUMPER_AR [%p][%x]\n\n", new_adr,\
		(void*)vault->ar_dump - new_adr);
		exit(-1);
		return (vault->ar_dump);
	}
	ft_printf("\033[36mjumped to [%p] - offset [%x]\033[0m\n"\
	, new_adr, new_adr - start_adr);
	return (new_adr);
}
