/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arr_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/* to sort dotfiles, pretend the dot doesn't exist, except for . && .. */
static void	advance_hidden_names(char **str)
{
	if (*str[0] == '.')
	{
		if (!(*(*str + 1) == '.' || !*(*str + 1)))
			++*str;
	}
}

/* sort by name, alphabetically */
static int	compare_names_alpha(t_directory *cont1, t_directory *cont2)
{
	char	*str1;
	char	*str2;

	str1 = cont1->s_dirent.d_name;
	advance_hidden_names(&str1);
	str2 = cont2->s_dirent.d_name;
	advance_hidden_names(&str2);
	return (ft_strcmp(str1, str2));
}

///* sort by name, reverse alphabetically */
//static int	compare_names_reverse(t_directory *cont1, t_directory *cont2)
//{
//	char	*str1;
//	char	*str2;
//
//	str1 = cont1->s_dirent.d_name;
//	advance_hidden_names(&str1);
//	str2 = cont2->s_dirent.d_name;
//	advance_hidden_names(&str2);
//	return (ft_strcmp(str2, str1));
//}

/* sort an array of pointers to list nodes */
void		sort_arr_lst(t_list **arr)
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
