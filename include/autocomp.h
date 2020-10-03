/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:40:54 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/24 21:21:49 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMP_H
# define AUTOCOMP_H
# include <dirent.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "shell.h"
# include "edit_line.h"

typedef struct		s_autocomp
{
	t_array			tab_a;
	int				first_time;
	size_t			index;
	t_string		line_tmp;
	t_string		path;
	t_string		str;
	size_t			cursor_tmp;
	int				nl;
}					t_autocomp;

typedef struct		s_aut_info
{
	DIR				*dirp;
	struct dirent	*dp;
}					t_aut_info;

void				init_str(t_autocomp *autocomp, t_line *line);
void				join_cs(t_autocomp *autocomp, char *ptr, char *ptr2);
int					verif_if_fnc(size_t i, char *str);
int					cmd_fnc(t_autocomp *autocomp);
int					create_tab_a(t_autocomp *autocomp);
void				my_read(t_line *l, int *first_time);
int					cmp_buf(int *value, char *buf);
size_t				get_end_erase(t_line *line);
size_t				get_start_erase(t_line *line);
void				print_auto(t_line *l, t_autocomp *autocomp);
#endif
