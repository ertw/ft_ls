/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <erik@himself.in>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:35:17 by ewilliam          #+#    #+#             */
/*   Updated: 2017/03/08 12:22:52 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_errx(int e, const char *s)
{
	dprintf(2, "%s\n", s);
	exit(e);
}

typedef struct			s_output
{
	char				name[256];
	struct s_output		*next;
	mode_t				mode;
}						t_output;

typedef struct			s_input
{
	struct s_output		*head;
	struct s_input		*next;
}						t_input;

typedef struct			s_node
{
    int					data;
    struct s_node*		left;
    struct s_node*		right;
}						t_node;

t_node					*create_node(int data)
{
	t_node	*new_node;

	if (!(new_node = malloc(sizeof(*new_node))))
		ft_errx(1, "Unable to allocate memory for node");
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int		compare_int(int left, int right)
{
	if (left > right)
		return (1);
	if (left < right)
		return (-1);
	return (0);
}

void	display_node(t_node *node)
{
	if (node)
		printf("%d\n", node->data);
}

void	display_tree(t_node *node)
{
	if (!node)
		return;
	printf("%d",node->data);
    if(node->left != NULL)
        printf("(L:%d)",node->left->data);
    if(node->right != NULL)
        printf("(R:%d)",node->right->data);
    printf("\n");
	display_tree(node->left);
	display_tree(node->right);
}

typedef int (*comparer)(int, int);
typedef void (*callback)(t_node*);

t_node* insert_node(t_node *root, comparer compare, int data)
{
	int		is_left;
	int		r;
	t_node	*cursor;
	t_node	*prev;

	if (!root)
		root = create_node(data);
	else
	{
		is_left = 0;
		r = 0;
		cursor = root;
		prev = NULL;
		while (cursor)
		{
			r = compare(data, cursor->data);
			prev = cursor;
			if (r < 0)
			{
				is_left = 1;
				cursor = cursor->left;
			}
			else if (r > 0)
			{
				is_left = 0;
				cursor = cursor->right;
			}
		}
		if (is_left)
			prev->left = create_node(data);
		else
			prev->right = create_node(data);
	}
	return (root);
}

void	traverse(t_node *root, callback cb)
{
	t_node	*cursor;
	t_node	*prev;

	if (!root)
		return;
	cursor = root;
	while (cursor)
	{
		if (cursor->left)
		{
			cb(cursor);
			cursor = cursor->right;
		}
		else
		{
			prev = cursor->left;
			while (prev->right && prev->right != cursor)
				prev = prev->right;
			if (prev->right)
			{
				prev->right = cursor;
				cursor = cursor->left;
			}
			else
			{
				prev->right = NULL;
				cb(cursor);
				cursor = cursor->right;
			}
		}
	}
}

int		main(int ac, char **av)
{
	DIR		 		*dirp = NULL;
	struct dirent	*dptr = NULL;
	struct stat		*stats = NULL;
	unsigned short	arg = 1;

	stats = ft_memalloc(sizeof(*stats));
	while (arg < ac)
	{
		printf("Try open: %s\n", av[arg]);
		stat(av[arg], stats);
		printf("%s is %s\n", av[arg], S_ISREG(stats->st_mode) ? "a file" : "not a file");
		if (!(dirp = opendir(av[arg])))
			dprintf(2, "%s: No such file or directory\n", av[arg]);
		++arg;
	}
	while (dirp && (dptr = readdir(dirp)) != NULL)
	{
		stat(dptr->d_name, stats);
		printf("%s\n", S_ISDIR(stats->st_mode) ? "dir" : "file");
	}
	if (dirp)
		(void)closedir(dirp);



#define SIZE 9
	int a[SIZE] = {8,3,10,1,6,14,4,7,13};
	int i = 0;
	t_node * root = NULL;
	while (i < SIZE)
	{
		root = insert_node(root, compare_int, a[i]);
		i++;
	}
	display_tree(root);
//	traverse(root, display_node);

}
