/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:07:03 by ewilliam          #+#    #+#             */
/*   Updated: 2017/03/06 13:32:49 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H
# ifdef __FreeBSD__
#  define _GNU_SOURCE
# endif
# include "../libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <sys/stat.h>
# include <inttypes.h>
#endif

#define C_DIR(node239) ((t_directory*)node239->content)
#define C_MET(node098) ((t_metadata*)node098->content)

#ifndef quad_t
# define quad_t long double
#endif

#ifdef __APPLE__
# define CONT_S_STAT_CTIM CONT_S_STAT.st_ctimespec.tv_sec
# define BLOCK_DIVISOR 1
#elif __linux__
# define CONT_S_STAT_CTIM CONT_S_STAT.st_ctim.tv_sec
# define BLOCK_DIVISOR 2

/* holds information about a file or directory */
typedef struct		s_directory
{
	struct stat	s_stats;		// copy of stat
	struct dirent	s_dirent;		// copy of dirent
	t_list		*metadata;		// meta list associated with this directory list
}			t_directory;

/* holds information about a list of files and directories */
typedef struct		s_metadata
{
	char		path[2048];			// path to here
	intmax_t	maxsize;		// bytes of largest file in dir
	quad_t		totalblocks;		// blockcount of dir
	t_list		*next;			// next meta list, if any
	t_list		*directory;		// directory list associated with this meta list
}			t_metadata;

t_list			*lst_dir_make(DIR *dirp, t_list *met);
char			*ft_pathjoin(const char *s1, const char *s2);
void			arr_foreach(t_list **arr, void (*visit)(t_list*));
void			lst_del_dir(void *content, size_t sizeofcontent);
void			lst_del_met(void *content, size_t sizeofcontent);
t_list			*lst_met_make(char *path);
void			lst_node_process(t_list *node);
void			sort_arr_lst(t_list **arr);
t_list			**lst_to_arr(t_list *head);
#endif
