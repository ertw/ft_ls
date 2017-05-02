#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head
#define C_DIR(node239) ((t_directory*)node239->content)
#define C_MET(node098) ((t_metadata*)node098->content)

/*
p ((t_metadata*)node->content)->path
p ((t_directory*)node->content)->s_dirent.d_name
p ((t_directory*)node->content)->metadata
*/

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
	char		*path;			// path to here
	intmax_t	maxsize;		// bytes of largest file in dir
	quad_t		totalblocks;		// blockcount of dir
	t_list		*next;			// next meta list, if any
	t_list		*directory;		// directory list associated with this meta list
}			t_metadata;

/* join to strings, putting a '/' in between them */
char			*ft_pathjoin(const char *s1, const char *s2)
{
	char	*tmp;
	char	*tmp2;
	tmp = ft_strjoin(s1, "/");
	tmp2 = ft_strjoin(tmp, s2);
	ft_strdel(&tmp);
	return (tmp2);
}

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
//	ft_strdel(&((t_metadata*)content)->path);
	ft_memdel((void**)(t_metadata*)&content);
}

/* try to open a path, if that fails, print error */
DIR			*open_dir(const char *path)
{
	DIR	*dirp;

	if (!(dirp = opendir(path)))
		dprintf(2, "%s: No such file or directory\n", "C_META(parent_meta)->path");
	else
		return (dirp);
	return (NULL);
}

/* recursively create the list */
t_list			*lst_dir_make(DIR *dirp, t_list *met)
{
	t_list		*node = NULL;
	struct dirent	*direntptr;
	t_directory	directory;

	if (!(direntptr = readdir(dirp)))
		return (NULL);
	{
		stat(direntptr->d_name, &directory.s_stats);
		ft_memmove(&directory.s_dirent, direntptr, sizeof(*direntptr));
		directory.metadata = met;
		node = ft_lstnew(&directory, sizeof(directory));
		node->next = lst_dir_make(dirp, met);
	}
	return (node);
}

/* create a meta node */
t_list			*lst_met_make(char *path)
{
	DIR		*dirp;
	t_metadata	met;
	t_list		*this;

	dirp = open_dir(path);
	this = ft_lstnew(&met, sizeof(met));
	{
		met.path = path;
		met.maxsize = 0;
		met.totalblocks = 0;
		met.next = NULL;
		C_MET(this)->directory = lst_dir_make(dirp, this);
	}
	ft_memdel((void*)&dirp);
	return (this);
}

/* print out each node's word */
void			lst_node_print(t_list *node)
{
	printf("%s\n", C_DIR(node)->s_dirent.d_name);
}

/* print the node, and if it's a directory, push a new meta */
void			lst_node_process(t_list *node)
{
	t_list	*cursor;

	if (!node)
		return ;
	lst_node_print(node);
	if (S_ISDIR(C_DIR(node)->s_stats.st_mode))
	{
		if (!(ft_strequ("..", C_DIR(node)->s_dirent.d_name)
			|| ft_strequ(".", C_DIR(node)->s_dirent.d_name)))
		{
			cursor = C_DIR(node)->metadata;
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = lst_met_make(C_DIR(node)->s_dirent.d_name);
			printf("<DIR>\n");
		}
	}
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

/* some say, this is the most important function... */
int			main(void)
{
	t_list		*head;
	t_list		*cursor;
	t_list		**arr;

	head= lst_met_make(".");
	cursor = head;
	while (cursor)
	{
		arr = lst_to_arr(C_MET(head)->directory);
		sort_arr_lst(arr);
		arr_foreach(arr, lst_node_process);
		ft_memdel((void*)&arr);
		cursor = cursor->next;
	}
	ft_lstdel(&head, lst_del_meta);
}
