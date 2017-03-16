#include "ft_ls.h"
#include <iso646.h>


int		lst_ishead(t_list *head, t_list *node)
{
	if (node == head)
		return (1);
	return (0);
}

//#define lst_ishead(head, head) (!!((node) == (head)))
#define lst_istail(node) (!!(node)->next == NULL)
#define lst_size(list) ((list)->size)
#define lst_head(list) ((list)->head)
#define lst_tail(list) ((list)->tail)
//#define lst_istail(node) ((node)->next == NULL ? 1 : 0)
//#define lst_ishead(head, node) ((head)->head == (node) ? 1 : 0)
#define lst_content(node) ((node)->content)
#define lst_next(node) ((node)->next)
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head

void		lst_insert(t_list **alst, void *content, size_t size)
{
	t_list	*tmp;

	tmp = *alst;
	*alst = ft_lstnew(content, size);
	(*alst)->next = tmp;
}

int		main(int ac, char **av)
{
	int	arg = 1;
	t_list	*head, *cursor;

	head = NULL;
	cursor = NULL;
	if (ac < 2)
		return (-1);
	while (arg < ac)
	{
		while (cursor)
		{	
			if (IS_HEAD and (ft_strcmp((char*)cursor->content, av[arg]) > 0))
			{
				lst_insert(&head, av[arg], sizeof(av[arg]) * ft_strlen(av[arg]));
				break;
			}
			else if (IS_TAIL or (ft_strcmp((char*)cursor->next->content, av[arg]) > 0))
			{
				lst_insert(&cursor->next, av[arg], sizeof(av[arg]) * ft_strlen(av[arg]));
				break;
			}
			cursor = cursor->next;
		}
		if (!head)
			head = ft_lstnew(av[arg], sizeof(av[arg]) * ft_strlen(av[arg]));
		cursor = head;
		++arg;
	}
	cursor = head;
	while (cursor)
	{
		printf("%s:", (char*)cursor->content);
		cursor = cursor->next;
	}
	printf("\na b: %d\n", ft_strcmp("a", "b"));
	printf("b a: %d\n", ft_strcmp("b", "a"));
}
