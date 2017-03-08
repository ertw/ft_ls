/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <erik@himself.in>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:35:17 by ewilliam          #+#    #+#             */
/*   Updated: 2017/03/07 20:29:51 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

typedef struct			s_output
{
	char				name[256];
	struct s_output		*next;
	mode_t				mode;
}						t_output;

typedef struct			s_input
{
	struct s_output		*head;
	struct s_input		*next;
}						t_input;

int		ft_errx(int e, const char *s)
{
	dprintf(2, "%s\n", s);
	exit(e);
}

int		main(int ac, char **av)
{
	DIR		 		*dirp = NULL;
	struct dirent	*dptr = NULL;
	struct stat		*stats = NULL;
	unsigned short	arg = 0;

	stats = ft_memalloc(sizeof(*stats));
	if (!(dirp = opendir("ss")))
		ft_errx(1, "<TODO>: No such file or directory");
	while ((dptr = readdir(dirp)) != NULL)
	{
		stat(dptr->d_name, stats);
		printf("%s\n", S_ISDIR(stats->st_mode) ? "dir" : "file");
	}
	(void)closedir(dirp);
}
