/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_dir_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
 ** recursively create the list
*/

t_list			*lst_dir_make(DIR *dirp, t_list *met)
{
	t_list			*node;
	struct dirent	*direntptr;
	t_directory		directory;

	node = NULL;
	if (!(direntptr = readdir(dirp)))
		return (NULL);
	stat(direntptr->d_name, &directory.s_stats);
	ft_memmove(&directory.s_dirent, direntptr, sizeof(*direntptr));
	directory.metadata = met;
	node = ft_lstnew(&directory, sizeof(directory));
	node->next = lst_dir_make(dirp, met);
	return (node);
}
