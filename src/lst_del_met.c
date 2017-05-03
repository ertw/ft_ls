/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_del_met.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** delete each meta node
*/

void			lst_del_met(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_lstdel(&((t_metadata*)content)->directory, &lst_del_dir);
	ft_memdel((void**)(t_metadata*)&content);
}
