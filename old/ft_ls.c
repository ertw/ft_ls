#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head

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

void		lst_insert(t_list **alst, void *content, size_t size)
{
	t_list	*tmp;

	tmp = *alst;
	*alst = ft_lstnew(content, size);
	(*alst)->next = tmp;
}

t_opts			parseflags(char *flags)
{
	t_opts	opts;

	opts.l = 0;
	opts.R = 0;
	opts.r = 0;
	opts.t = 0;
	return (opts);
}

t_list			*processinput(int ac, char **av)
{
	unsigned short	arg = 1;
	t_list		*head = NULL;
	t_list		*cursor = NULL;
	t_input		input;

	while (av[arg] && *av[arg] == '-')
	{
		while (*av[arg]++)
		{
			printf("%c\n", *av[arg]);
		}
		++arg;
	}
	while (arg < ac)
	{
//		ft_bzero(input.name, 256);
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

	while ((dptr = readdir(dirp)))
	{
		while (cursor)
		{
			if (IS_HEAD && (ft_strcmp((char*)cursor->content, dptr->d_name) < 0))
			{
				lst_insert(&head, dptr->d_name, 256);
				break;
			}
			else if (IS_TAIL || (ft_strcmp((char*)cursor->next->content, dptr->d_name) < 0))
			{
				lst_insert(&cursor->next, dptr->d_name, 256);
				break;
			}
			cursor = cursor->next;
		}
		if (!head)
			head = ft_lstnew(dptr->d_name, 256);
		cursor = head;
	}
	cursor = head;
	while (cursor)
	{
		while (cursor && *(char*)cursor->content == '.')
			cursor = cursor->next;
		if (cursor)
		{
			printf("%s\n", (char*)cursor->content);
			cursor = cursor->next;
		}
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
		cursor = cursor->next;
	}
	return (head);
}

int			main(int ac, char **av)
{
	processfiles(processinput(ac, av));
	return (0);
}
