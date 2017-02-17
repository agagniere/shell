/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:16:45 by malaine           #+#    #+#             */
/*   Updated: 2017/02/14 17:41:11 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_LINE_H
#define MULTI_LINE_H

typedef struct		s_multi
{
	t_array	pos_rtn;
	t_array	size_str;
	int		nb_rtn;
	int		index1;
	int		index2;
	int		index3;
}					t_multi;

int     multi_init(t_multi *multi);

extern t_multi g_multi;

#endif
