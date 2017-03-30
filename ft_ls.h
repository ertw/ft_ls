/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:07:03 by ewilliam          #+#    #+#             */
/*   Updated: 2017/03/06 13:32:49 by ewilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H

# include "./libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <sys/stat.h>
#endif

#ifndef quad_t
# define quad_t long double
#endif

#ifdef __APPLE__
# define CONT_S_STAT_CTIM CONT_S_STAT.st_ctimespec.tv_sec
# define BLOCK_DIVISOR 1
#elif __linux__
# define CONT_S_STAT_CTIM CONT_S_STAT.st_ctim.tv_sec
# define BLOCK_DIVISOR 2
#endif
