/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_cap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:10:35 by galy              #+#    #+#             */
/*   Updated: 2018/05/02 19:10:49 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

size_t	ft_strlen_cap(t_vault *vault, const char *s)
{
	size_t	i;
	void	*start_adr;
	void	*max_adr;
	void	*cur_adr;

	i = 0;
	start_adr = (vault->ar_dump != NULL) ? vault->ar_dump : vault->f_dump;
	max_adr = (void*)start_adr + vault->f_stat.st_size;
	while (s[i] != '\0')
	{
		i++;
		cur_adr = ((void*)s + i);
		if (cur_adr == max_adr)
			break ;
	}
	return (i);
}
