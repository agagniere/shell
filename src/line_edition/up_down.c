/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:21:59 by malaine           #+#    #+#             */
/*   Updated: 2017/03/08 16:06:13 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "shell.h"

void		ft_up(t_line *l)
{
	if (g_history.index > 0)
		bi_change_str(l, &g_history, search_history(l, &g_history, 1));
}

void		ft_down(t_line *l)
{
	if (g_history.index < g_history.tab_h.size)
		bi_change_str(l, &g_history, search_history(l, &g_history, 0));
}
