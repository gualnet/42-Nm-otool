/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset_jumper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:45:53 by galy              #+#    #+#             */
/*   Updated: 2018/04/06 14:28:34 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	*set_start_adr(t_vault *vault)
{
	// if (vault->fat_dump != NULL && vault->ar_dump == NULL && vault->o_dump == NULL)
	if (vault->fat_dump != NULL)
		return (vault->fat_dump);
	else if (vault->fat_dump == NULL && vault->ar_dump != NULL)
		return (vault->ar_dump);
	else if (vault->fat_dump == NULL && vault->ar_dump == NULL && vault->o_dump != NULL)
		return (vault->o_dump);
	else
		ft_printf("pb set_start_adr in offset_jumper.c\n");
	return (NULL);
}

void	*offset_jumper(t_vault *vault, void *ptr, long jumpsize)
{
	void	*start_adr;
	void	*max_adr;
	void	*new_adr;
	
	start_adr = set_start_adr(vault);
	new_adr = NULL;
	max_adr = (void*)start_adr + vault->f_stat.st_size;
	new_adr = (void*)ptr + jumpsize;

	if (new_adr < start_adr)
		ft_printf("000001\n");
	if (new_adr > max_adr)
		ft_printf("000002\n");

	if (new_adr == NULL || new_adr < start_adr || new_adr > max_adr)
	{
		ft_printf("\n\nERROR JUMPER_AR [%p][%x]\n\n", new_adr,\
		(void*)vault->ar_dump - new_adr);
		return (NULL);
	}
	// ft_printf("\033[36mjumped to [%p] - offset [%x]\033[0m\n"\
	// , new_adr, new_adr - start_adr);
	return (new_adr);
}

// void	*offset_inner_jumper(t_vault *vault, void *inner_start, void *ptr, long jumpsize)
// {
// 	void	*start_adr;
// 	void	*max_adr;
// 	void	*new_adr;
	
// 	start_adr = set_start_adr(vault);
// 	new_adr = NULL;
// 	max_adr = (void*)start_adr + vault->f_stat.st_size;
// 	new_adr = (void*)ptr + jumpsize;
// 	if (new_adr == NULL || new_adr < vault->ar_dump || new_adr > max_adr)
// 	{
// 		ft_printf("\n\nERROR JUMPER_AR [%p][%x]\n\n", new_adr,\
// 		(void*)vault->ar_dump - new_adr);
// 		return (NULL);
// 	}
// 	// ft_printf("\033[36mjumped to [%p] - offset [%x]\033[0m\n"\
// 	// , new_adr, new_adr - start_adr);
// 	return (new_adr);
// }