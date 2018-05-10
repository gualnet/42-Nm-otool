/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:32:54 by galy              #+#    #+#             */
/*   Updated: 2018/05/10 18:24:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			dal_2(t_sect_lnk *sect_lnk)
{
	t_sect_lnk	*tmp;
	t_sect_lnk	*sve;

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

int			delete_all_lst(t_vault *vault)
{
	t_lc_lnk	*tmp;
	t_lc_lnk	*sve;

	if (vault->lc_lst == NULL)
		return (0);
	tmp = vault->lc_lst;
	while (tmp != NULL)
	{
		if (tmp->sect_lst.lnk_64 != NULL)
		{
			dal_2(tmp->sect_lst.lnk_64);
			tmp->sect_lst.lnk_64 = NULL;
		}
		sve = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = sve;
	}
	vault->lc_lst = NULL;
	return (0);
}

t_lc_lnk	*add_new_lclink(t_vault *vault, void *adr)
{
	t_lc_lnk	*new_elem;
	t_lc_lnk	*tmp;
	void		*entry;

	tmp = vault->lc_lst;
	if (NULL == (new_elem = (t_lc_lnk*)malloc(sizeof(*new_elem))))
		return (NULL);
	new_elem->lc = adr;
	new_elem->sect_lst.lnk_64 = NULL;
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
	return (new_elem);
}

void		*ans_2(void *adr)
{
	t_sect_lnk	*new_elem;

	if (NULL == (new_elem = (t_sect_lnk*)malloc(sizeof(*new_elem))))
		return (NULL);
	new_elem->sect = adr;
	new_elem->next = NULL;
	return (new_elem);
}

t_sect_lnk	*add_new_sectlnk(t_lc_lnk *lc_lnk, void *adr)
{
	t_sect_lnk	*new_elem;
	t_sect_lnk	*tmp;
	void		*entry;
	int			i;

	tmp = lc_lnk->sect_lst.lnk_64;
	new_elem = ans_2(adr);
	if (tmp == NULL)
	{
		tmp = new_elem;
		entry = new_elem;
	}
	else
	{
		entry = (void*)lc_lnk->sect_lst.lnk_64;
		i = 0;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		tmp->next = new_elem;
	}
	lc_lnk->sect_lst.lnk_64 = entry;
	return (new_elem);
}
