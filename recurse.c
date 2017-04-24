#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head
#define C_DIR(node239) ((t_directory*)node239->content)
#define C_MET(node098) ((t_metadata*)node098->content)

/* holds information about a file or directory */
typedef struct		s_directory
{
	struct stat	s_stats;
	struct dirent	s_dirent;
	t_list		*metadata;
}			t_directory;

/* holds information about a list of files and directories */
typedef struct		s_metadata
{
	char		*path;			// path to here
	intmax_t	maxsize;		// bytes of largest file in dir
	quad_t		totalblocks;		// blockcount of dir
	t_list		*next;			// next meta list, if any
	t_list		*directory;		// directory list associated with this meta list
}			t_metadata;

/* delete each list node */
void			lst_del_directory(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_memdel((void**)(t_directory*)&content);
}

/* delete each meta node */
void			lst_del_meta(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_lstdel(&((t_metadata*)content)->directory, &lst_del_directory);
	ft_strdel(&((t_metadata*)content)->path);
	ft_memdel((void**)(t_metadata*)&content);
}

/* recursively create the list */
t_list			*lst_dir_make(DIR *dirp)
{
	t_list		*node = NULL;
	struct dirent	*direntptr;
	t_directory	directory;

	if (!(direntptr = readdir(dirp)))
		return (NULL);
	{
		stat(direntptr->d_name, &directory.s_stats);
		ft_memmove(&directory.s_dirent, direntptr, sizeof(*direntptr));
		node = ft_lstnew(&directory, sizeof(directory));
		node->next = lst_dir_make(dirp);
	}
	return (node);
}

/* create a meta node */
t_list			*lst_met_make(char *path)
{
	t_metadata	met;

	met.path = path;
	met.maxsize = 0;
	met.totalblocks = 0;

	return (ft_lstnew(&met, sizeof(met)));
}

/* print out each node's word */
void			lst_node_print(t_list *node)
{
	printf("%s\n", C_DIR(node)->s_dirent.d_name);
}

void			arr_foreach(t_list **arr, void (*visit)(t_list*))
{
	int	i;

	i = 0;
	while (arr[i])
	{
		visit(arr[i]);
		i++;
	}
}

/* delete each dir list node */
void			lst_del_dir(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_memdel((void**)(t_directory*)&content);
}

/* delete each meta list node */
void			lst_del_met(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_strdel(&((t_metadata*)content)->path);
	ft_memdel((void**)(t_metadata*)&content);
}

/* put t_list pointers into array */
t_list			**lst_to_arr(t_list *head)
{
	t_list		*cursor;
	int		len;
	int		i;
	t_list		**arr;

	cursor = head;
	len = 0;
	i = 0;
	while (cursor)
	{
		len++;
		cursor = cursor->next;
	}
	cursor = head;
	arr = ft_memalloc(sizeof(cursor) * (len + 1));
	while (i < len)
	{
		arr[i] = cursor;
		cursor = cursor->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/* to sort dotfiles, pretend the dot doesn't exist, except for . && .. */
void				advance_hidden_names(char **str)
{
	if (*str[0] == '.')
	{
		if (!(*(*str + 1) == '.' || !*(*str + 1)))
			++*str;
	}
}

/* sort by name, alphabetically */
int				compare_names_alpha(t_directory *cont1, t_directory *cont2)
{
	char	*str1;
	char	*str2;

	str1 = cont1->s_dirent.d_name;
	advance_hidden_names(&str1);
	str2 = cont2->s_dirent.d_name;
	advance_hidden_names(&str2);
	return (ft_strcmp(str1, str2));
}

/* sort by name, reverse alphabetically */
int				compare_names_reverse(t_directory *cont1, t_directory *cont2)
{
	char	*str1;
	char	*str2;

	str1 = cont1->s_dirent.d_name;
	advance_hidden_names(&str1);
	str2 = cont2->s_dirent.d_name;
	advance_hidden_names(&str2);
	return (ft_strcmp(str2, str1));
}

/* sort an array of pointers to list nodes */
void sort_arr_lst(t_list **arr)
{
	t_list			*temp;
	unsigned short i;

	i = 1;
	while (arr[i])
	{
		if (compare_names_alpha(C_DIR(arr[i]), C_DIR(arr[i - 1])) < 0)
		{
			temp = arr[i - 1];
			arr[i - 1] = arr[i];
			arr[i] = temp;
			i = 1;
		}
		else
			i++;
	}
}

int			main(void)
{
	t_list		*head;
	DIR		*dirp;
	t_list		**arr;

	if (!(dirp = opendir(".")))
		dprintf(2, "%s: No such file or directory\n", "C_META(parent_meta)->path");
//	head = lst_dir_make(dirp);
	head = lst_met_make(".");
	ft_memdel((void*)&dirp);
	arr = lst_to_arr(head);
	sort_arr_lst(arr);
	arr_foreach(arr, lst_node_print);
	ft_memdel((void*)&arr);
//	ft_lstdel(&head, lst_del_content);
	ft_lstdel(&head, lst_del_meta);
}
