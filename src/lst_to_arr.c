/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** put t_list pointers into array
*/

t_list			**lst_to_arr(t_list *head)
{
	t_list	*cursor;
	int		len;
	int		i;
	t_list	**arr;

	cursor = head;
	len = 0;
	i = 0;
	while (cursor)
	{
		len++;
		cursor = cursor->next;
	}
	cursor = head;
	arr = ft_memalloc(sizeof(cursor) * (len + 1));
	while (i < len)
	{
		arr[i] = cursor;
		cursor = cursor->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
