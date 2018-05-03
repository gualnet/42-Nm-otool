/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:43:12 by galy              #+#    #+#             */
/*   Updated: 2018/04/25 18:43:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char	*extract_file_name(char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	while (i > 0)
	{
		if (path[i] == '/')
			return (path + i + 1);
		i--;
	}
	return (path);
}
