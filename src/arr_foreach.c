/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_foreach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
 ** iterate over an array of *t_list
*/

void			arr_foreach(t_list **arr, void (*visit)(t_list*))
{
	int	i;

	i = 0;
	while (arr[i])
	{
		visit(arr[i]);
		i++;
	}
}
