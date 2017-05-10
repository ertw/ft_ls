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
** print out filename
*/

static void		print_file(t_list *node)
{
	printf("%s\n", C_DIR(node)->s_dirent.d_name);
}

/*
** print out full directory path
*/

static void		print_directory(t_list *node)
{
	printf("%s:\n", C_DIR(node)->path);
}

/*
** print the node, and if it's a directory, push a new meta
*/

void			lst_node_process(t_list *node)
{
	if (!node)
		return ;
//	printf("<PATH: %s >\n", C_DIR(node)->path);
//	if (!S_ISDIR(C_DIR(node)->s_stats.st_mode))
	if (C_DIR(node)->s_dirent.d_type != DT_DIR)
		print_file(node);
	else
	{
		if (ft_strequ("..", C_DIR(node)->s_dirent.d_name)
			|| ft_strequ(".", C_DIR(node)->s_dirent.d_name))
			return ;
		print_directory(node);
	}
}
