#include "ft_ls.h"

typedef struct			s_input
{
	char			name[256];
	t_list			*head;
}				t_input;

typedef struct			s_opts
{
	int					l;
	int					R;
	int					r;
	int					t;
}						t_opts;

t_list			*processinput(int ac, char **av)
{
	unsigned short	arg = 1;
	t_list		*head = NULL;
	t_list		*cursor = NULL;
	t_input		input;

	while (arg < ac)
	{
		ft_bzero(input.name, 256);
		ft_memmove(input.name, av[arg], ft_strlen(av[arg]));
		if (cursor)
		{
			cursor->next = ft_lstnew(&input, sizeof(input));
			cursor = cursor->next;
		}
		else
		{
			head = ft_lstnew(&input, sizeof(input));
			cursor = head;
		}
		++arg;
	}
	return (head);
}

void			readfiles(DIR *dirp)
{
	struct dirent	*dptr;
	t_list		*head = NULL;
	t_list		*cursor = NULL;
	t_list		*tmp = NULL;

	while ((dptr = readdir(dirp)))
	{
		while (cursor)
		{
			if (ft_strcmp(dptr->d_name, (char*)cursor->content) > 0)
			{
				tmp = cursor->next;
				cursor->next = ft_lstnew(dptr->d_name, 256);
				cursor->next->next = tmp;
				cursor = head;
			}
			else if (ft_strcmp(dptr->d_name, (char*)cursor->content) < 0)
			{
				tmp = cursor->next;
				cursor->next = ft_lstnew(dptr->d_name, 256);
				cursor->next->next = tmp;
				cursor = head;
			}
			else
				cursor = cursor->next;
		}
		if (!cursor)
		{
			head = ft_lstnew(dptr->d_name, 256);
			cursor = head;
		}
	}
	cursor = head;
	while (cursor)
	{
		printf("%s\n", (char*)cursor->content);
		cursor = cursor->next;
	}
}

t_list			*processfiles(t_list *head)
{
	DIR		*dirp = NULL;
	t_list		*cursor = NULL;

	cursor = head;
	while (cursor)
	{
		if (!(dirp = opendir(((t_input*)cursor->content)->name)))
			dprintf(2, "%s: No such file or directory\n", ((t_input*)cursor->content)->name);
		else
		{
			readfiles(dirp);
			closedir(dirp);
		}
//		printf("%s\n", ((t_input*)cursor->content)->name);
		cursor = cursor->next;
	}
	return (head);
}

int			main(int ac, char **av)
{
	processfiles(processinput(ac, av));
	return (0);
}
