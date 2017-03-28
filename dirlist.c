#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head
#define CONT_DIRENT ((t_container*)cursor->content)->s_dirent
#define CONT_DIRENT_D_NAME ((t_container*)cursor->content)->s_dirent.d_name
#define CONT_DIRENT_D_NAME_N ((t_container*)cursor->next->content)->s_dirent.d_name
#define CONT_S_STAT ((t_container*)cursor->content)->s_stat
#define CONT_S_STAT_ATIM CONT_S_STAT.st_atim.tv_sec
#define CONT_S_STAT_MTIM CONT_S_STAT.st_mtim.tv_sec
#define CONT_S_STAT_CTIM CONT_S_STAT.st_ctim.tv_sec
//	printf("dirent: %s\n", cont.s_dirent.d_name);
//	printf("stat  : %ld\n", cont.s_stat.st_size);

typedef struct			s_container
{
	struct dirent		s_dirent;
	struct stat		s_stat;
	struct s_container	*next;
}				t_container;

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
	t_list		*node;
	t_container	cont;
	DIR		*dirp;
	struct stat	stats;

	ft_memmove(&cont.s_dirent, dptr, sizeof(*dptr));
	stat(dptr->d_name, &stats);
	ft_memmove(&cont.s_stat, &stats, sizeof(stats));
	return (ft_lstnew(&cont, sizeof(cont)));
}

/* loop through the directory and sort*/
t_list		*read_dir(void)
{
	t_list		*head, *cursor;
	struct dirent	*dptr;
	DIR		*dirp;

	head = NULL;
	cursor = NULL;
	dirp = opendir(".");
	while((dptr = readdir(dirp)))
	{
		while (cursor)
		{
			if (IS_HEAD && (ft_strcmp(CONT_DIRENT_D_NAME, dptr->d_name) > 0))
			{
				lst_inst_node(&head, make_lst(dptr));
				break;
			}
			else if (IS_TAIL || (ft_strcmp(CONT_DIRENT_D_NAME_N, dptr->d_name) > 0))
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
	closedir(dirp);
	return (head);
}



/* delete each list node*/
void		lst_del(t_list *head)
{
	t_list	*cursor;
	t_list	*tmp;

	if (!head)
		return ;
	cursor = head;
	while (cursor)
	{
		tmp = cursor->next;
		free(cursor->content);
		free(cursor);
		cursor = tmp;
	}
}

int		main(void)
{
	char	timestr[13];

	t_list	*head, *cursor;

	head = NULL;
	cursor = NULL;
	head = read_dir();
	cursor = head;
//	memmove(timestr, ctime(&CONT_S_STAT_ATIM), 26);
//	write(1, timestr + 4, 12);
	while (cursor)
	{
		printf("%- 7ld ", CONT_S_STAT.st_size);
		strncpy(timestr, ctime(&CONT_S_STAT_ATIM) + 4, 12);
		printf("%s ", timestr);
		printf("%s \n", CONT_DIRENT_D_NAME);
		cursor = cursor->next;
	}
	lst_del(head);
}
