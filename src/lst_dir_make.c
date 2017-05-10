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

t_list				*lst_dir_make(DIR *dirp, t_list **met)
{
	t_list			*node;
	struct dirent	*direntptr;
	t_directory		directory;
	char				*path;
	t_list			*tmp;

	if (!(direntptr = readdir(dirp)))
	{
		return (NULL);
	}
	ft_bzero(&directory, sizeof(directory));
	asprintf(&path, "%s/%s", C_MET((*met))->path, direntptr->d_name);
	if (direntptr->d_type == DT_DIR)
	{
		tmp = (*met)->next;
		(*met)->next = lst_met_make(path);
		(*met)->next->next = tmp;
	}
	ft_memmove(&directory.s_dirent, direntptr, sizeof(*direntptr));
	stat(path, &directory.s_stats);
	directory.metadata = met;
	directory.path = path;
	node = ft_lstnew(&directory, sizeof(directory));
	node->next = lst_dir_make(dirp, met);
	return (node);
}

//t_list			*lst_dir_make(DIR *dirp, t_list *met)
//{
//	t_list			*node;
//	struct dirent	*direntptr;
//	t_directory		directory;
//	char				*path;
//
//	node = NULL;
//	if (!(direntptr = readdir(dirp)))
//		return (NULL);
//	ft_memmove(&directory.s_dirent, direntptr, sizeof(*direntptr));
//	path = ft_pathjoin(C_MET(met)->path, direntptr->d_name);
//	stat(path, &directory.s_stats);
//	ft_strdel(&path);
//	directory.metadata = met;
//	node = ft_lstnew(&directory, sizeof(directory));
//	node->next = lst_dir_make(dirp, met);
//	return (node);
//}
