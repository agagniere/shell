/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:02:52 by malaine           #+#    #+#             */
/*   Updated: 2017/03/07 18:29:58 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include "autocomp.h"
#include <curses.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <term.h>
#include <unistd.h>
#include <string.h>
int			check_longer(t_array *tab_a)
{
	void		*iterator;
	t_string	*tmp;
	int 		max;

	max = 0;
	iterator = ARRAY_ITERATOR(tab_a);
	while (ARRAY_HASNEXT(tab_a, iterator))
	{
		tmp = (t_string *)iterator;
		if (max < tmp->size)
			max = tmp->size;
	}
	return (max);
}

void		print_auto(int largeur, t_autocomp *autocomp)
{
	int space;
	int i;
	int max_name = check_longer(&autocomp->tab_a);
	int col_sauv = largeur / (max_name + 3);
	int col = col_sauv;
	t_string	*tmp;

	i = 0;
	autocomp->nl = 0;
	while (i < autocomp->tab_a.size)
	{
		tmp = ARRAY_GETT(t_string, &autocomp->tab_a, i);
		if (i < col)
		{
			if (i == autocomp->index)
				do_term("mr");
			ft_putstr((char *)tmp->data);
			space = max_name - tmp->size;
			while (space-- >= 0)
				ft_putstr(" ");
			do_term("me");
			ft_putstr("  ");
			i++;
		}
		else
		{
			ft_putstr("\n");
			autocomp->nl++;
			col = col + col_sauv;
		}
	}
	ft_putstr("\n");
	autocomp->nl++;
}
