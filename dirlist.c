#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head
#define CONT_DIRENT ((t_container*)cursor->content)->s_dirent
#define CONT_DIRENT_D_NAME ((t_container*)cursor->content)->s_dirent.d_name
#define CONT_DIRENT_D_NAME_N ((t_container*)cursor->next->content)->s_dirent.d_name
#define CONT_S_STAT ((t_container*)cursor->content)->s_stat
#define CONT_S_STAT_ATIM CONT_S_STAT.st_atim.tv_sec
#define CONT_S_STAT_MTIM CONT_S_STAT.st_mtim.tv_sec
#define CONT_GROUPNAME ((t_container*)cursor->content)->groupname
#define CONT_USERNAME ((t_container*)cursor->content)->username
#define CONT_MODE ((t_container*)cursor->content)->mode
#define CONT_BLOCKS ((t_container*)cursor->content)->blocks
#define CONT_NLINKS ((t_container*)cursor->content)->nlinks
#define MAX_USERNAME_LEN 33
#define MAX_GROUPNAME_LEN 33

//	printf("dirent: %s\n", cont.s_dirent.d_name);
//	printf("stat  : %ld\n", cont.s_stat.st_size);
//	printf("group: %s\n", grp->gr_name);
//	printf("username: %s\n", pwd->pw_name);

typedef struct			s_container
{
	struct dirent		s_dirent;
	struct stat		s_stat;
	char			username[MAX_USERNAME_LEN];
	char			groupname[MAX_GROUPNAME_LEN];
	uid_t			uid;
	gid_t			gid;
	mode_t			mode;
	nlink_t			nlinks;
	quad_t			blocks;
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

void		set_groupname(t_container *cont)
{
	struct group	*grp;
	grp = getgrgid(cont->gid);
	ft_memmove(cont->groupname, grp->gr_name, sizeof(grp->gr_name));
}

void		set_username(t_container *cont)
{
	struct passwd	*pwd;
	pwd = getpwuid(cont->uid);
	ft_memmove(cont->username, pwd->pw_name, sizeof(pwd->pw_name));
}

void		set_uid(t_container *cont, struct stat *stats)
{
	cont->uid = stats->st_uid;
}

void		set_gid(t_container *cont, struct stat *stats)
{
	cont->gid = stats->st_gid;
}

void		set_mode(t_container *cont, struct stat *stats)
{
	cont->mode = stats->st_mode;
}

void		set_nlinks(t_container *cont, struct stat *stats)
{
	cont->nlinks = stats->st_nlink;
}

void		set_g_blocks(t_container *cont, struct stat *stats)
{
	cont->blocks = stats->st_blocks;
}

/* this will create each node*/
t_list		*make_lst(struct dirent *dptr)
{
	t_list		*node;
	t_container	cont;
	DIR		*dirp;
	struct stat	stats;

//	printf("block %ld\n", stats.st_blocks);
	ft_memmove(&cont.s_dirent, dptr, sizeof(*dptr));
	stat(dptr->d_name, &stats);
	ft_memmove(&cont.s_stat, &stats, sizeof(stats));
	set_uid(&cont, &stats);
	set_gid(&cont, &stats);
	set_username(&cont);
	set_groupname(&cont);
	set_mode(&cont, &stats);
	set_nlinks(&cont, &stats);
	set_g_blocks(&cont, &stats);
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

void		print_permissions(t_list *cursor)
{
	printf((S_ISDIR(CONT_MODE)) ? "d" : "-");
	printf((CONT_MODE & S_IRUSR) ? "r" : "-");
	printf((CONT_MODE & S_IWUSR) ? "w" : "-");
	if (CONT_MODE & S_ISVTX)
		printf((CONT_MODE & S_IXUSR) ? "s" : "S");
	else
		printf((CONT_MODE & S_IXUSR) ? "x" : "-");
	printf((CONT_MODE & S_IRGRP) ? "r" : "-");
	printf((CONT_MODE & S_IWGRP) ? "w" : "-");
	if (CONT_MODE & S_ISVTX)
		printf((CONT_MODE & S_IXGRP) ? "s" : "S");
	else
		printf((CONT_MODE & S_IXGRP) ? "x" : "-");
	printf((CONT_MODE & S_IROTH) ? "r" : "-");
	printf((CONT_MODE & S_IWOTH) ? "w" : "-");
	if (CONT_MODE & S_ISVTX)
		printf((CONT_MODE & S_IXOTH) ? "t" : "T");
	else
		printf((CONT_MODE & S_IXOTH) ? "x" : "-");

}

quad_t		get_total_blocks(t_list *head)
{
	t_list	*cursor;
	quad_t	blocks;

	cursor = head;
	blocks = 0;
	while (cursor)
	{
		blocks += CONT_BLOCKS;
		cursor = cursor->next;
	}
	return (blocks / 2);
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
	printf("Total %Lf\n", get_total_blocks(head));
	while (cursor)
	{
		printf("Blox: %Lf ", CONT_BLOCKS);
		print_permissions(cursor);
		printf(" %d ", CONT_NLINKS);
		printf("%s ", CONT_USERNAME);
		printf("%s ", CONT_GROUPNAME);
		printf("% 7lld ", CONT_S_STAT.st_size);
		strncpy(timestr, ctime(&CONT_S_STAT_CTIM) + 4, 12);
		printf("%s ", timestr);
		printf("%s \n", CONT_DIRENT_D_NAME);
		cursor = cursor->next;
	}
	lst_del(head);
}
