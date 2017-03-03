/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:40:54 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/03 21:03:28 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMP_H
# define AUTOCOMP_H

typedef struct		s_autocomp
{
	t_array			tab_a;
	int				first_time;
	int				index;
	t_string		path;
	t_string		str;
}					t_autocomp;

typedef struct		s_aut_info
{
	DIR				*dirp;
	struct dirent	*dp;
}					t_aut_info;
#endif
