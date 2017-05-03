/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_foreach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
p ((t_metadata*)node->content)->path
p ((t_metadata*)cursor->content)->path
p ((t_metadata*)node->content)->path
p ((t_metadata*)node->content)->directory
p ((t_metadata*)cursor->content)->maxsize
p ((t_metadata*)cursor->next->content)->path
p ((t_directory*)((t_metadata*)node->content)->directory)->s_stats
p ((t_directory*)node->content)->s_dirent.d_name
p ((t_directory*)node->content)->metadata
p cursor->next
*/

/*
 **(IN JEREMY CLARKSON VOICE) some say this is the most important function...
*/

int			main(void)
{
	t_list		*head;
	t_list		*cursor;
	t_list		**arr;

	head = lst_met_make("./test");
	cursor = head;
	while (cursor)
	{
		arr = lst_to_arr(C_MET(cursor)->directory);
		sort_arr_lst(arr);
		arr_foreach(arr, lst_node_process);
		ft_memdel((void*)&arr);
		cursor = cursor->next;
	}
	ft_lstdel(&head, lst_del_met);
}
