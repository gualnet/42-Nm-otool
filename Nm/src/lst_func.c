/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:32:54 by galy              #+#    #+#             */
/*   Updated: 2018/03/28 19:21:27 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		dal_2(t_sect_lnk *sect_lnk)
{
	t_sect_lnk	*tmp;
	t_sect_lnk	*sve;

	tmp = sect_lnk;
	while (tmp != NULL)
	{
		// ft_printf("[%s][%s]\n", tmp->sect->sectname, tmp->sect->segname);
		sve = tmp->next;
		free(tmp);
		tmp = sve;
	}
	return (0);
}	

int		delete_all_lst(t_vault *vault)
{
	t_lc_lnk	*tmp;
	t_lc_lnk	*sve;

	if(vault->lc_lst == NULL)
		return (0);
	tmp = vault->lc_lst;
	while (tmp != NULL)
	{
		// ft_printf("tmp->lc->cmd [%x]\n", tmp->lc->cmd);
		// ft_printf("tmp->lc->cmdsize [%x]\n", tmp->lc->cmdsize);
		if(tmp->sect_lst != NULL)
		{
			dal_2(tmp->sect_lst);
			tmp->sect_lst = NULL;
			// ft_printf("tmp->sect_lst[%p]\n",tmp->sect_lst);
		}
		sve = tmp->next;
		free(tmp);
		tmp = sve;
	}
	return (0);
}

t_lc_lnk	*add_new_lclink(t_vault *vault, void *adr)
{
	// ft_printf("\nCALL ADD_NEW_LC_LINK [%p]\n", vault->lc_lst);
	
	t_lc_lnk	*new_elem;
	t_lc_lnk	*tmp;
	void		*entry;
	
	tmp = vault->lc_lst;
	if (NULL == (new_elem = (t_lc_lnk	*)malloc(sizeof(*new_elem))))
		return (NULL);
	new_elem->lc = adr;
	new_elem->sect_lst = NULL;
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
	// ft_printf("\nEND ADD_NEW_LC_LINK [%p][%p]\n", vault->lc_lst, entry);
	return (new_elem);
}

t_sect_lnk	*add_new_sectlnk(t_lc_lnk *lc_lnk, void *adr)
{
	// ft_printf("\nCALL ADD_NEW_SECTION LINK [%p]\n", lc_lnk->sect_lst);
	
	t_sect_lnk	*new_elem;
	t_sect_lnk	*tmp;
	void		*entry;

	tmp = lc_lnk->sect_lst;
	// ft_printf("---0\n");	
	if (NULL == (new_elem = (t_sect_lnk	*)malloc(sizeof(*new_elem))))
		return (NULL);
	// ft_printf("---1\n");
	new_elem->sect = adr;
	new_elem->next = NULL;
	if (tmp == NULL)
	{
		// ft_printf("---2\n");
		tmp = new_elem;
		entry = new_elem;
	}
	else
	{
		// ft_printf("---2\n");
		int i = 0;
		entry = (void*)lc_lnk->sect_lst;
		while (tmp->next != NULL)
		{
			// ft_printf("---4\n");
			tmp = tmp->next;
			i++;
			// if (i == 5)
			// 	exit(0);
		}
		// ft_printf("---4\n");
		tmp->next = new_elem;

	}
	// ft_printf("---8\n");
	lc_lnk->sect_lst = entry;
	// ft_printf("\nEND ADD_NEW_SECTION LINK [%p]\n", lc_lnk->sect_lst);
	// ft_printf("---9\n");
	return (new_elem);
}