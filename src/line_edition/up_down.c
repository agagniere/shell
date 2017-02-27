/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:21:59 by malaine           #+#    #+#             */
/*   Updated: 2017/02/27 19:18:33 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void		ft_up(t_line *l)
{
	if (g_history.index > 0)
	{	g_history.index--;
		bi_change_str(l, &g_history);
	}
}

void		ft_down(t_line *l)
{
	if (g_history.index < g_history.tab_h.size - 1)
	{
		g_history.index++;
		bi_change_str(l, &g_history);
	}
}
