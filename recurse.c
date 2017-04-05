#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head
#define DIRECTORY ((t_directory*)cursor->content)
#define META ((t_metadata*)cursor->content)
/*
 * read in a path from the read stack
 * if it's a file, print it
 * if it's a dir, print every file in it
 * 	if any file is a directory, add it to the read stack
 * if it's something else, gracefully error
*/

typedef struct		s_directory
{
	char		*name;			// path and name of file
}			t_directory;

typedef struct		s_metadata
{
	char		*path;			// path to here
	t_list		*head;
}			t_metadata;

/* delete each list node */
void					lst_del_meta(void *content, size_t sizeofcontent)
{
	ft_strdel(&((t_metadata*)content)->path);
	ft_memdel((void**)(t_metadata*)&content);
}

/* delete each list node */
void					lst_del_directory(void *content, size_t sizeofcontent)
{
//	ft_strdel(&((t_metadata*)content)->path);
//	ft_memdel((void**)(t_metadata*)&content);
}

/* create each directory node */
t_list					*lst_makenode_directory(char *name)
{
	t_list		*node;
	t_directory	directory;

	return (ft_lstnew(&directory, sizeof(directory)));
}

/* create each metadata node */
t_list					*lst_makenode_meta(char *name)
{
	t_list		*node;
	t_metadata	meta;

	meta.path = ft_strdup(name);
	return (ft_lstnew(&meta, sizeof(meta)));
}

/* print out each list node */
void			testprint(t_list *head)
{
	t_list	*cursor;

	cursor = head;
	while (cursor)
	{
		printf("%s\n", META->path);
		cursor = cursor->next;
	}
	ft_lstdel(&head, &lst_del_meta);
}

/* read from arguments */
t_list			*processinput(int ac, char **av)
{
	unsigned short	arg = 1;
	t_list		*head = NULL;
	t_list		*cursor = NULL;
	t_metadata	meta;

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
			cursor->next = lst_makenode_meta(av[arg]);
			cursor = cursor->next;
		}
		else
		{
			head = lst_makenode_meta(av[arg]);
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
