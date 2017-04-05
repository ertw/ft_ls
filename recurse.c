#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head

/*
 * read in a path from the read stack
 * if it's a file, print it
 * if it's a dir, print every file in it
 * 	if any file is a directory, add it to the read stack
 * if it's something else, gracefully error
*/

typedef struct		s_container
{
	char		*name;			// path and name of file
}			t_container;

/* delete each list node */
void					lst_del(t_list *head)
{
	t_list	*cursor;
	t_list	*tmp;

	if (!head)
		return ;
	cursor = head;
	while (cursor)
	{
		tmp = cursor->next;
		ft_strdel(&((t_container*)cursor->content)->name);
		ft_memdel((void**)&cursor->content);
		ft_memdel((void**)&cursor);
		cursor = tmp;
	}
}

/* create each node */
t_list					*lst_make_node(char *name)
{
	t_list		*node;
	t_container	cont;

	cont.name = ft_strdup(name);
	return (ft_lstnew(&cont, sizeof(cont)));
}

/* print out each list node */
void			testprint(t_list *head)
{
	t_list	*cursor;

	cursor = head;
	while (cursor)
	{
		printf("%s\n", ((t_container*)cursor->content)->name);
		cursor = cursor->next;
	}
	lst_del(head);
}

/* read from arguments */
t_list			*processinput(int ac, char **av)
{
	unsigned short	arg = 1;
	t_list		*head = NULL;
	t_list		*cursor = NULL;
	t_container	cont;

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
		if (cursor)
		{
			cursor->next = lst_make_node(av[arg]);
			cursor = cursor->next;
		}
		else
		{
			head = lst_make_node(av[arg]);
			cursor = head;
		}
		++arg;
	}
	return (head);
}

int			main(int ac, char **av)
{
	testprint(processinput(ac, av));
	return (0);
}
