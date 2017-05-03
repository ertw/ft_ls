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
	char	*path;

	if (!node)
		return ;
	lst_node_print(node);
	if (ft_strequ("1", C_DIR(node)->s_dirent.d_name))
		printf("<INSIDE!>\n");
	if (S_ISDIR(C_DIR(node)->s_stats.st_mode))
	{
		if (ft_strequ("..", C_DIR(node)->s_dirent.d_name)
			|| ft_strequ(".", C_DIR(node)->s_dirent.d_name))
			return ;
		cursor = C_DIR(node)->metadata;
		while (cursor)
		{
			printf("<NODE>\n");
			cursor = cursor->next;
		}
		path = ft_pathjoin(C_MET(C_DIR(node)->metadata)->path,
				C_DIR(node)->s_dirent.d_name);
		cursor = lst_met_make(path);
		printf("<PATH: %s>\n", path);
		ft_strdel(&path);
	}
}
