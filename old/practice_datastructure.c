#include "ft_ls.h"
#define MAX_STR 31
#define NODE(node5h321) ((t_container*)node5h321->content)

/* the container that will be in each node */
typedef struct		s_container
{
	char		str[MAX_STR + 1];
}			t_container;

/* recursively create the list */
t_list			*lst_make(FILE *in)
{
	t_list		*node = NULL;
	char		str[MAX_STR + 1];
	t_container	cont;

	if (fscanf(in, "%s", str) == EOF)
		return (NULL);
	ft_strcpy(cont.str, str);
	node = ft_lstnew(&cont, sizeof(cont));
	node->next = lst_make(in);
	return (node);
}

/* print out each node's word */
void			lst_node_print(t_list *node)
{
	printf("%s\n", NODE(node)->str);
}

/* delete each list node */
void			lst_del_content(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_memdel((void**)(t_container*)&content);
}

int			main(void)
{
	t_list		*head;
	FILE		*in;

	in = fopen("file.txt", "r");
	head = lst_make(in);
	ft_lstiter(head, lst_node_print);
	ft_lstdel(&head, lst_del_content);
}
