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
p ((t_metadata*)(**met)->content)->path
p ((t_metadata*)node->content)->directory
p ((t_metadata*)cursor->content)->directory
p ((t_metadata*)cursor->content)->maxsize
p ((t_metadata*)cursor->content)->path
p ((t_metadata*)cursor->next->content)->path
p ((t_directory*)((t_metadata*)node->content)->directory)->s_stats
p ((t_directory*)node->content)->s_stats
p ((t_directory*)node->content)->s_stats.st_mode
p ((t_directory*)node->content)->s_dirent
p ((t_directory*)node->content)->s_dirent.d_name
p ((t_directory*)node->content)->metadata
p ((t_metadata*)((t_directory*)node->content)->metadata)->path
p cursor->next
*/

/*
 ** creates and nulls out flags structure
 */

t_flags *init_flags(void)
{
	t_flags	*flags;
	flags = malloc(sizeof(*flags));
	flags->l = 0;
	flags->R = 0;
	flags->a = 0;
	flags->r = 0;
	flags->t = 0;
	return (flags);
}

/*
 ** process the arguments
 */

int read_args(int argc, char **argv, t_flags *flags)
{
	int ch;

	while ((ch = getopt(argc, argv, "lRart")) != -1)
	{
		switch (ch)
		{
			case 'l':
				printf("long format flag\n");
				flags->l = 1;
				break;
			case 'R':
				printf("recursive flag\n");
				flags->R = 1;
				break;
			case 'a':
				printf("include hidden flag\n");
				flags->a = 1;
				break;
			case 'r':
				printf("print reverse flag\n");
				flags->r = 1;
				break;
			case 't':
				printf("sort by time modified flag\n");
				flags->t = 1;
				break;
		}
	}
	return (0);
}

/*
 **(IN JEREMY CLARKSON VOICE) some say this is the most important function...
*/

int			main(int argc, char **argv)
{
	t_list		*head;
	t_list		*cursor;
	t_list		**arr;
	t_flags		*flags;

	flags = init_flags();
	read_args(argc, argv, flags);
	head = lst_met_make("./test");
	cursor = head;
	while (cursor)
	{
		arr = lst_to_arr(lst_dir_make(C_MET(cursor)->dirp, &cursor));
		sort_arr_lst(arr);
		arr_foreach(arr, lst_node_process);
		ft_memdel((void*)&arr);
		cursor = cursor->next;
	}
	ft_lstdel(&head, lst_del_met);
	ft_memdel((void*)&flags);
}
