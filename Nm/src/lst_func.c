/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:32:54 by galy              #+#    #+#             */
/*   Updated: 2018/03/15 12:07:12 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_lc_lnk	*add_new_link(t_vault *vault, void *adr)
{
	// ft_printf("\nCALL ADD_NEW_LINK [%p]\n", vault->lc_lst);
	
	t_lc_lnk	*new_elem;
	t_lc_lnk	*tmp;
	void		*entry;
	
	tmp = vault->lc_lst;
	if (NULL == (new_elem = (t_lc_lnk	*)malloc(sizeof(*new_elem))))
		return (NULL);
	new_elem->lc = adr;
	new_elem->next = NULL;
	if (vault->lc_lst == NULL)
	{
		vault->lc_lst = new_elem;
		entry = new_elem;
	}
	else
	{
		entry = (void*)vault->lc_lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
	vault->lc_lst = entry;
	// ft_printf("\nEND ADD_NEW_LINK [%p][%p]\n", vault->lc_lst, entry);
	return (new_elem);
}