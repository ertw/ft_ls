/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <erik@himself.in>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:35:17 by ewilliam          #+#    #+#             */
/*   Updated: 2017/03/08 17:01:17 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_errx(int e, const char *s)
{
	dprintf(2, "%s\n", s);
	exit(e);
}

typedef struct			s_output
{
	char				name[256];
	mode_t				mode;
}						t_output;

typedef struct			s_input
{
	struct stat			*stats;
}						t_input;

int		main(int ac, char **av)
{
	DIR		 		*dirp = NULL;
	struct dirent	*dptr = NULL;
	struct stat		*stats = NULL;
	unsigned short	arg = 1;
	t_input			*input = NULL;
	t_list			*lst_input = NULL;
	t_list			*lst_cursor = NULL;

	stats = ft_memalloc(sizeof(*stats));
	input = ft_memalloc(sizeof(*input));
	input->stats = ft_memalloc(sizeof(*stats));
	lst_input = ft_lstnew(input, sizeof(input));
	lst_cursor = lst_input;
	while (arg < ac)
	{
		printf("Try open: %s\n", av[arg]);
		stat(av[arg], input->stats);
		input->stats = stats;
		printf("%s is %s\n", av[arg], S_ISREG(stats->st_mode) ? "a file" : "not a file");
		if (!(dirp = opendir(av[arg])))
			dprintf(2, "%s: No such file or directory\n", av[arg]);
		++arg;
		lst_cursor->next = ft_lstnew(NULL, 0);
		lst_cursor = lst_cursor->next;
	}
	while (dirp && (dptr = readdir(dirp)) != NULL)
	{
		stat(dptr->d_name, stats);
		printf("%s\n", S_ISDIR(stats->st_mode) ? "dir" : "file");
	}
	if (dirp)
		(void)closedir(dirp);
//	free(&stats);
	free(&(input->stats));
//	free(&input);

	typedef struct	s_int
	{
		int			n;
	}				t_int;
	
	#define SIZE 9
	int i = 0;

	t_list	*head = NULL;
	t_list	*cursor = NULL;
	t_int	*container;

	while (i < SIZE)
	{
		if (cursor)
		{
			cursor->next = ft_lstnew(container, sizeof(container));
			cursor = cursor->next;
		}
		else
		{
			head = ft_lstnew(container, sizeof(container));
			cursor = head;
		}
		((t_int*)cursor->content)->n = i;
		i++;
	}
	cursor = head;
	while (cursor)
	{
		printf("%d\n", ((t_int*)cursor->content)->n);
		cursor = cursor->next;
	}
}
