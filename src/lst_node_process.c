/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_node_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** print out each node's word
*/

static void		lst_node_print(t_list *node)
{
	printf("%s\n", C_DIR(node)->s_dirent.d_name);
}

/*
** print the node, and if it's a directory, push a new meta
*/

void			lst_node_process(t_list *node)
{
	t_list	*cursor;
	t_list	*tmp;
	char	*path;

	if (!node)
		return ;
	lst_node_print(node);
//	printf("<NAME: %s >\n", C_DIR(node)->s_dirent.d_name);
//	printf("<MODE: %d >\n", (C_DIR(node)->s_stats.st_mode));
//	printf("<ISDIR: %d >\n", S_IFDIR == (C_DIR(node)->s_stats.st_mode & S_IFMT));
	if (S_ISDIR(C_DIR(node)->s_stats.st_mode))
	{
//		printf("<DIR>\n");
		if (ft_strequ("..", C_DIR(node)->s_dirent.d_name)
			|| ft_strequ(".", C_DIR(node)->s_dirent.d_name))
			return ;
		cursor = C_DIR(node)->metadata;
		tmp = cursor->next;
		path = ft_pathjoin(C_MET(C_DIR(node)->metadata)->path,
				C_DIR(node)->s_dirent.d_name);
		cursor->next = lst_met_make(path);
		cursor->next->next = tmp;
		ft_strdel(&path);
	}
}
