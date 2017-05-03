/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_met_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/* try to open a path, if that fails, print error */
static DIR	*open_dir(const char *path)
{
	DIR	*dirp;

	if (!(dirp = opendir(path)))
		dprintf(2, "%s: No such file or directory\n", path);
	else
		return (dirp);
	return (NULL);
}

/* create a meta node */
t_list		*lst_met_make(char *path)
{
	DIR		*dirp;
	t_metadata	met;
	t_list		*node;

	if (!(dirp = open_dir(path)))
		return (NULL);
	ft_memmove(met.path, path, ft_strlen(path) + 1);
	met.maxsize = 0;
	met.totalblocks = 0;
	met.next = NULL;
	node = ft_lstnew(&met, sizeof(met));
	C_MET(node)->directory = lst_dir_make(dirp, node);
	ft_memdel((void*)&dirp);
	return (node);
}
