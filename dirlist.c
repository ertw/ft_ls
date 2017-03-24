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

struct stat	read_stats(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	return (stats);
}

t_list		*read_dir(void)
{
	t_list		*head, *cursor;
	struct dirent	*dptr;
	struct stat	stats;
	DIR		*dirp;
	t_container	cont;

	head = NULL;
	cursor = NULL;
	cont.next = NULL;
	dirp = opendir(".");
	dptr = readdir(dirp);
	ft_memmove(&cont.s_dirent, dptr, sizeof(*dptr));
	stat(dptr->d_name, &stats);
	ft_memmove(&cont.s_stat, &stats, sizeof(stats));
	printf("dirent: %s\n", cont.s_dirent.d_name);
	printf("stat  : %llu\n", cont.s_stat.st_size);
	head = ft_lstnew(&cont, sizeof(cont));
	ft_memdel((void**)&dptr);
	ft_memdel((void**)&dirp);
	return (head);
}

#define CONT_DIRENT_D_NAME ((t_container*)head->content)->s_dirent.d_name

int		main(void)
{
	t_list	*head;
	head = read_dir();
	printf("%s\n", CONT_DIRENT_D_NAME);
}
