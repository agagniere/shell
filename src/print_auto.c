/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:02:52 by malaine           #+#    #+#             */
/*   Updated: 2017/03/07 20:12:59 by malaine          ###   ########.fr       */
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


void		print_auto(t_line *l, t_autocomp *autocomp)
{
	int space;
	int i;
	int ii;
	int more = 0;
	int test;
	int max_name = check_longer(&autocomp->tab_a);
	int col_sauv = l->largeur / (max_name + 3);
	int col = col_sauv;
	t_string	*tmp;

	i = 0;
	ii = 0;
	autocomp->nl = 0;
	if (col > 0)
	{
		if (autocomp->tab_a.size > l->hauteur -1 && (l->hauteur - 1) * col_sauv < autocomp->tab_a.size)
		{
			more = 1;
			ft_ctrl_l(l);
			ft_putstr("\n");
			if (autocomp->index >= l->hauteur - 1)
				i = autocomp->index + 2 - l->hauteur;
			col = col + i;
	}
		if (more == 0)
			test = autocomp->tab_a.size;
		else if (more == 1)
			test = l->hauteur - 1;
	while (ii < test)
	{
		if (more == 1)
			more = 0;
		tmp = ARRAY_GETT(t_string, &autocomp->tab_a, i);
		if (i < col)
		{
			i == autocomp->index ? do_term("mr") : do_term("me") ;
			ft_putstr((char *)tmp->data);
			space = max_name - tmp->size;
			while (space-- >= 0)
				ft_putstr(" ");
			do_term("me");
			ft_putstr("  ");
			i++;
			ii++;
		}
		else
		{
			autocomp->nl++;
			ft_putstr("\n");
			col = col + col_sauv;
		}
	}
	}
}
