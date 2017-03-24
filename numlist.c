#include "ft_ls.h"

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
			if (IS_HEAD && (ft_strcmp((char*)cursor->content, av[arg]) > 0))
			{
				lst_insert(&head, av[arg], sizeof(av[arg]) * ft_strlen(av[arg]));
				break;
			}
			else if (IS_TAIL || (ft_strcmp((char*)cursor->next->content, av[arg]) > 0))
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
}
