#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head
#define CONT(node098gh) ((t_container*)node098gh->content)
#define CONT_DIRENT ((t_container*)cursor->content)->s_dirent
#define CONT_S_STAT ((t_container*)cursor->content)->s_stat
#define CONT_S_STAT_ATIM CONT_S_STAT.st_atim.tv_sec
#define CONT_S_STAT_MTIM CONT_S_STAT.st_mtim.tv_sec
#define CONT_GROUPNAME ((t_container*)cursor->content)->groupname
#define CONT_USERNAME ((t_container*)cursor->content)->username
#define CONT_MODE ((t_container*)cursor->content)->mode
#define CONT_BLOCKS ((t_container*)cursor->content)->blocks
#define CONT_NLINKS ((t_container*)cursor->content)->nlinks
#define METADATA ((t_container*)head->content)->metadata
#define MAX_USERNAME_LEN 33
#define MAX_GROUPNAME_LEN 33

typedef struct			s_metadata
{
	uintmax_t			maxsize;			//largest file, for printf width
	quad_t				totalblocks;			//sum of blocks
}						t_metadata;

typedef struct			s_container
{
	struct dirent		s_dirent;			// removeme!
	struct stat			s_stat;				// removeme!
	char				username[MAX_USERNAME_LEN];
	char				groupname[MAX_GROUPNAME_LEN];
	uid_t				uid;
	gid_t				gid;
	mode_t				mode;
	nlink_t				nlinks;				// number of links
	quad_t				blocks;				// blocks of the file
	off_t				size;				// bytes of file
	t_metadata			*metadata;
}						t_container;

void					lst_inst_node(t_list **alst, t_list *node)
{
	t_list	*tmp;

	tmp = *alst;
	*alst = node;
	(*alst)->next = tmp;
}

struct stat				read_stats(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	return (stats);
}

void					set_groupname(t_container *cont)
{
	struct group	*grp;

	grp = getgrgid(cont->gid);
	ft_memmove(cont->groupname, grp->gr_name, sizeof(grp->gr_name));
}

void					set_username(t_container *cont)
{
	struct passwd	*pwd;

	pwd = getpwuid(cont->uid);
	ft_memmove(cont->username, pwd->pw_name, sizeof(pwd->pw_name));
}

void					set_uid(t_container *cont, struct stat *stats)
{
	cont->uid = stats->st_uid;
}

void					set_gid(t_container *cont, struct stat *stats)
{
	cont->gid = stats->st_gid;
}

void					set_mode(t_container *cont, struct stat *stats)
{
	cont->mode = stats->st_mode;
}

void					set_nlinks(t_container *cont, struct stat *stats)
{
	cont->nlinks = stats->st_nlink;
}

void					set_blocks(t_container *cont, struct stat *stats)
{
	cont->blocks = stats->st_blocks;
}

void					set_metadata(t_container *cont, t_metadata *metadata)
{
	cont->metadata = metadata;
}

void					set_blocks_meta(t_container *cont)
{
	cont->metadata->totalblocks += cont->blocks;
}

void					set_size(t_container *cont, struct stat *stats)
{
	cont->size = stats->st_size;
}

void					set_maxsize_meta(t_container *cont)
{
	if (cont->size > cont->metadata->maxsize)
		cont->metadata->maxsize = cont->size;
}

/* this will create each node*/
t_list					*lst_make_node(struct dirent *dptr, t_metadata *metadata)
{
	t_list		*node;
	t_container	cont;
	DIR			*dirp;
	struct stat	stats;

	ft_memmove(&cont.s_dirent, dptr, sizeof(*dptr));
	stat(dptr->d_name, &stats);
	ft_memmove(&cont.s_stat, &stats, sizeof(stats));
	set_metadata(&cont, metadata);
	set_uid(&cont, &stats);
	set_gid(&cont, &stats);
	set_username(&cont);
	set_groupname(&cont);
	set_mode(&cont, &stats);
	set_nlinks(&cont, &stats);
	set_blocks(&cont, &stats);
	set_blocks_meta(&cont);
	set_maxsize_meta(&cont);
	return (ft_lstnew(&cont, sizeof(cont)));
}

t_metadata				*init_metadata(t_metadata *metadata)
{
	metadata = ft_memalloc(sizeof(metadata));
	metadata->totalblocks = 0;
	metadata->maxsize = 0;
	return (metadata);
}

/*
 * loop through the directory and sort
 * */
t_list					*read_dir(DIR *dirp)
{
	t_list		*head;
	t_list		*cursor;
	struct dirent	*dptr;
	t_metadata	*metadata;
	metadata = init_metadata(metadata);
	head = NULL;
	cursor = NULL;
	while ((dptr = readdir(dirp)))
	{
		while (cursor)
		{
			if (IS_HEAD && (ft_strcmp(CONT(cursor)->s_dirent.d_name, dptr->d_name) > 0))
			{
				lst_inst_node(&head, lst_make_node(dptr, metadata));
				break ;
			}
			else if (IS_TAIL || (ft_strcmp(CONT(cursor->next)->s_dirent.d_name, dptr->d_name) > 0))
			{
				lst_inst_node(&cursor->next, lst_make_node(dptr, metadata));
				break ;
			}
			cursor = cursor->next;
		}
		if (!head)
			head = lst_make_node(dptr, metadata);
		cursor = head;
	}
	return (head);
}

/*
 * delete each list node
 */
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
		ft_memdel((void**)&cursor->content);
		ft_memdel((void**)&cursor);
		cursor = tmp;
	}
}

void					print_permissions(t_list *cursor)
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

quad_t					get_total_blocks(t_list *head)
{
	return (CONT(head)->metadata->totalblocks / BLOCK_DIVISOR);
}

t_list					*processfiles(t_list *head)
{
	DIR			*dirp;
	t_list		*cursor;

	cursor = NULL;
	dirp = NULL;
	cursor = head;
	while (cursor)
	{
		if (!(dirp = opendir(CONT(cursor)->s_dirent.d_name)))
			dprintf(2, "%s: No such file or directory\n", (CONT(cursor)->s_dirent.d_name));
		else
		{
			read_dir(dirp);
			closedir(dirp);
		}
		cursor = cursor->next;
	}
	return (head);
}

t_list					*processinput(int ac, char **av)
{
	unsigned short	arg;
	t_list			*head;
	t_list			*cursor;
	t_container		cont;

	arg = 1;
	head = NULL;
	cursor = NULL;
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
		ft_memmove(CONT(cursor)->s_dirent.d_name, av[arg], ft_strlen(av[arg]));
		if (cursor)
		{
//			cursor->next = ft_lstnew(&cont, sizeof(cont));
			cursor->next = lst_make_node(dptr, metadata);
			cursor = cursor->next;
		}
		else
		{
//			head = ft_lstnew(&cont, sizeof(cont));
			head = lst_make_node(dptr, metadata);
			cursor = head;
		}
		++arg;
	}
	return (head);
}

int						main(void)
{
	char	timestr[13];
	t_list	*head;
	t_list	*cursor;
	int		sizelength;
	DIR		*dirp;

	head = NULL;
	cursor = NULL;
	dirp = opendir(".");
	head = read_dir(dirp);
	closedir(dirp);
	cursor = head;
	sizelength = 1 + ft_countplaces(CONT(head)->metadata->maxsize, 10);	// calc width for printing bytes
	printf("total %.Lf\n", get_total_blocks(head));
	while (cursor)
	{
		print_permissions(cursor);
		printf(" %lu ", CONT_NLINKS);
		printf("%s ", CONT_USERNAME);
		printf("%s", CONT_GROUPNAME);
		printf("% *ld ", sizelength, CONT_S_STAT.st_size);
		strncpy(timestr, ctime(&CONT_S_STAT_CTIM) + 4, 12);		// format time string
		printf("%s ", timestr);
		printf("%s \n", CONT(cursor)->s_dirent.d_name);
		cursor = cursor->next;
	}
	ft_memdel((void**)&METADATA);
	lst_del(head);
}
