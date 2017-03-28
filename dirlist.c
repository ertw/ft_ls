#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head

typedef struct			s_container
{
	struct dirent		s_dirent;
	struct stat		s_stat;
	struct s_container	*next;
}				t_container;

void		lst_insert(t_list **alst, void *content, size_t size)
{
	t_list	*tmp;

	tmp = *alst;
	*alst = ft_lstnew(content, size);
	(*alst)->next = tmp;
}

void		lst_inst_node(t_list **alst, t_list *node)
{
	t_list	*tmp;

	tmp = *alst;
	*alst = node;
	(*alst)->next = tmp;
}

struct stat	read_stats(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	return (stats);
}

/* this will create each node*/
t_list		*make_lst(struct dirent *dptr)
{
	t_container	cont;
	DIR		*dirp;
	struct stat	stats;
	t_list		*node;

	ft_memmove(&cont.s_dirent, dptr, sizeof(*dptr));
	stat(dptr->d_name, &stats);
	ft_memmove(&cont.s_stat, &stats, sizeof(stats));
	printf("dirent: %s\n", cont.s_dirent.d_name);
	printf("stat  : %ld\n", cont.s_stat.st_size);
	node = ft_lstnew(&cont, sizeof(cont));
//	ft_memdel((void**)&dirp);
	return (ft_lstnew(&cont, sizeof(cont)));
}

/* this will read dir in a while loop, and call make_lst*/
t_list		*read_dir(void)
{
	t_list		*head, *cursor;
	struct dirent	*dptr;
//	struct stat	stats;
	DIR		*dirp;
//	t_container	cont;

	head = NULL;
	cursor = NULL;
//	cont.next = NULL;
	dirp = opendir(".");
	while((dptr = readdir(dirp)))
	{
		while (cursor)
		{
			if (IS_HEAD && (ft_strcmp((char*)cursor->content, dptr->d_name) < 0))
			{
				lst_inst_node(&head, make_lst(dptr));
				break;
			}
			else if (IS_TAIL || (ft_strcmp((char*)cursor->next->content, dptr->d_name) < 0))
			{
				lst_inst_node(&cursor->next, make_lst(dptr));
				break;
			}
			cursor = cursor->next;
		}
		if (!head)
			head = make_lst(dptr);
		cursor = head;
	}
	
//	ft_memmove(&cont.s_dirent, dptr, sizeof(*dptr));
//	stat(dptr->d_name, &stats);
//	ft_memmove(&cont.s_stat, &stats, sizeof(stats));
//	printf("dirent: %s\n", cont.s_dirent.d_name);
//	printf("stat  : %ld\n", cont.s_stat.st_size);
//	head = ft_lstnew(&cont, sizeof(cont));
//	ft_memdel((void**)&dirp);
	return (head);
}

#define CONT_DIRENT ((t_container*)head->content)->s_dirent
#define CONT_DIRENT_D_NAME ((t_container*)head->content)->s_dirent.d_name
#define CONT_S_STAT ((t_container*)head->content)->s_stat
#define CONT_S_STAT_ATIM CONT_S_STAT.st_atim.tv_sec
#define CONT_S_STAT_MTIM CONT_S_STAT.st_mtim.tv_sec
#define CONT_S_STAT_CTIM CONT_S_STAT.st_ctim.tv_sec

int		main(void)
{
	char	timestr[27];

	t_list	*head;
	head = read_dir();
	memmove(timestr, ctime(&CONT_S_STAT_ATIM), 26);
	printf("%ld\n", CONT_S_STAT.st_size);
	write(1, timestr + 4, 12);
	ft_putendl(CONT_DIRENT_D_NAME);
	free(&CONT_DIRENT);
	free(head);
}
