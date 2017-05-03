/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_dir_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:51 by ewilliam          #+#    #+#             */
/*   Updated: 2016/11/29 18:10:39 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** join to strings, putting a '/' in between them
*/

char			*ft_pathjoin(const char *s1, const char *s2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(s1, "/");
	tmp2 = ft_strjoin(tmp, s2);
	ft_strdel(&tmp);
	return (tmp2);
}
