/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 04:55:01 by galy              #+#    #+#             */
/*   Updated: 2018/04/10 20:25:36 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		dal_2_32(t_sect_lnk_32 *sect_lnk)
{
	t_sect_lnk_32	*tmp;
	t_sect_lnk_32	*sve;

	tmp = sect_lnk;
	while (tmp != NULL)
	{
		sve = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = sve;
	}
	return (0);
}	

int		delete_all_lst_32(t_vault *vault)
{
	t_lc_lnk	*tmp;
	t_lc_lnk	*sve;

	if(vault->lc_lst == NULL)
		return (0);
	tmp = vault->lc_lst;
	while (tmp != NULL)
	{
		if(tmp->sect_lst.lnk_32 != NULL)
		{
			dal_2_32(tmp->sect_lst.lnk_32);
			tmp->sect_lst.lnk_32 = NULL;
		}
		sve = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = sve;
	}
	vault->lc_lst = NULL;
	return (0);
}

t_lc_lnk	*add_new_lclink_32(t_vault *vault, void *adr)
{
	// ft_printf("\nCALL ADD_NEW_LC_LINK 32 [%p]\n", vault->lc_lst);
	t_lc_lnk	*new_elem;
	t_lc_lnk	*tmp;
	void		*entry;
	
	tmp = vault->lc_lst;
	if (NULL == (new_elem = (t_lc_lnk*)malloc(sizeof(*new_elem))))
		return (NULL);
	new_elem->lc = adr;
	new_elem->sect_lst.lnk_32 = NULL;
	new_elem->next = NULL;
	if (vault->lc_lst == NULL)
	{
		vault->lc_lst = new_elem;
		entry = new_elem;
		// ft_printf("ENTRY POINT : %p \n", new_elem);
	}
	else
	{
		entry = (void*)vault->lc_lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
	vault->lc_lst = entry;
	// ft_printf("\nEND ADD_NEW_LC_LINK 32 [%p][%p]\n", vault->lc_lst, entry);
	return (new_elem);
}

t_sect_lnk_32	*add_new_sectlnk_32(t_lc_lnk *lc_lnk, void *adr)
{
	// ft_printf("\nCALL ADD_NEW_SECTION LINK [%p]\n", lc_lnk->sect_lst);
	t_sect_lnk_32	*new_elem;
	t_sect_lnk_32	*tmp;
	void		*entry;

	tmp = lc_lnk->sect_lst.lnk_32;
	if (NULL == (new_elem = (t_sect_lnk_32*)malloc(sizeof(*new_elem))))
		return (NULL);
	new_elem->sect_32 = adr;
	new_elem->next = NULL;
	if (tmp == NULL)
	{
		tmp = new_elem;
		entry = new_elem;
	}
	else
	{
		int i = 0;
		entry = (void*)lc_lnk->sect_lst.lnk_32;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		tmp->next = new_elem;

	}
	lc_lnk->sect_lst.lnk_32 = entry;
	// ft_printf("\nEND ADD_NEW_SECTION LINK [%p]\n", lc_lnk->sect_lst);
	return (new_elem);
}