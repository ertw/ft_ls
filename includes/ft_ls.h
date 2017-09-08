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

#ifndef FT_LS_H

# define FT_LS_H

# ifdef __APPLE__
#  define CONT_S_STAT_CTIM CONT_S_STAT.st_ctimespec.tv_sec
#  define BLOCK_DIVISOR 1
# elif __linux__
#  define _GNU_SOURCE
#  define CONT_S_STAT_CTIM CONT_S_STAT.st_ctim.tv_sec
#  define BLOCK_DIVISOR 2
# elif __FreeBSD__
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

# define C_DIR(node239) ((t_directory*)node239->content)
# define C_MET(node098) ((t_metadata*)node098->content)

/*
** holds information about a file or directory
**
**	s_stats;		copy of stat
**	s_dirent;		copy of dirent
**	*metadata;		meta list associated with this dirlist
*/

typedef struct		s_directory
{
	struct stat		s_stats;
	struct dirent	s_dirent;
	t_list			**metadata;
	char			*path;
}					t_directory;

/*
** holds information about a list of files and directories
**
** path[2048];			path to here
** maxsize;				bytes of largest file in dir
** totalblocks;			blockcount of dir
** *next;				next meta list, if any
** *directory;			dirlist associated with this meta list
*/

typedef struct		s_metadata
{
	char			path[2048];
	intmax_t		maxsize;
	long double		totalblocks;
	DIR			*dirp;
	t_list			*directory;
}					t_metadata;

/*
 ** holds flags
 */

typedef struct		s_flags
{
	int			l;
	int			R;
	int			a;
	int			r;
	int			t;
}					t_flags;

t_list				*lst_dir_make(DIR *dirp, t_list **met);
t_list				*lst_met_make(char *path);
char				*ft_pathjoin(const char *s1, const char *s2);
void				arr_foreach(t_list **arr, void (*visit)(t_list*));
void				lst_del_dir(void *content, size_t sizeofcontent);
void				lst_del_met(void *content, size_t sizeofcontent);
void				lst_node_process(t_list *node);
void				sort_arr_lst(t_list **arr);
t_list				**lst_to_arr(t_list *head);
#endif
