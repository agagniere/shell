/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 13:49:16 by jguthert          #+#    #+#             */
/*   Updated: 2017/02/09 19:05:44 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include <stdio.h>

void		ft_right2(t_line *l)
{
	printf("ok\n");
}


static t_actions const	g_actions[1] = {
	{ft_right2, {27, 91, 67, 0, 0, 0}, "RIGHT"},
//	{ft_left2, {27, 91, 68, 0, 0, 0}, "LEFT"},
};

static int		cmp_buf(int *value, char *buf)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (buf[i] != value[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int				actions(t_line *l)
{
	int	i;

	i = 0;
	while (g_actions[i].action != NULL)
	{
		if (cmp_buf((int *)g_actions[i].value, l->buffer) == 0)
		{
			g_actions[i].action(l);
			return (0);
		}
		i++;
	}
	return (1);
}
