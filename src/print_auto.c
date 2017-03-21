/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:02:52 by malaine           #+#    #+#             */
/*   Updated: 2017/03/16 15:37:21 by malaine          ###   ########.fr       */
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

typedef struct s_print_a
{
	int			space;
	int			i;
	int			get;
	int			max_name;
	int			nb_col;
	int			condition;
	int			nl;
	int			nb_elem;
	t_string	*tmp;
	bool		more;
}				t_print_a;

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
		if (max < (int)tmp->size)
			max = tmp->size;
	}
	return (max);
}

void		init_print_a(t_line *l, t_print_a *print_a, t_autocomp *autocomp)
{
	print_a->i = 0;
	print_a->max_name = check_longer(&autocomp->tab_a);
	print_a->nb_col = l->largeur / (print_a->max_name + 3);
	print_a->get = 0;
	print_a->nb_elem = print_a->nb_col;
	autocomp->nl = 0;
}

void		check_if_rotate(t_line *l, t_print_a *print_a, t_autocomp *autocomp)
{
	if ((l->hauteur - 1) * print_a->nb_col < (int)autocomp->tab_a.size)
	{
		print_a->more = 1;
		ft_ctrl_l(l);
		ft_putstr("\n");
		if ((int)autocomp->index >= l->hauteur - 1)
			print_a->get = autocomp->index + 2 - l->hauteur;
		print_a->nb_elem = print_a->nb_elem + print_a->get;
	}
}

void		print_elem(t_print_a *print_a, t_autocomp *autocomp)
{
	print_a->get == (int)autocomp->index ? do_term("mr") : do_term("me") ;
	ft_putstr((char *)print_a->tmp->data);
	print_a->space = print_a->max_name - print_a->tmp->size;
	while (print_a->space-- >= 0)
		ft_putstr(" ");
	do_term("me");
	ft_putstr("  ");
	print_a->get++;
	print_a->i++;
}

void		print_auto(t_line *l, t_autocomp *autocomp)
{
	t_print_a print_a;

	ft_end(l);
	do_term("cd");
	printf("\n");
	init_print_a(l, &print_a, autocomp);
	if (print_a.nb_elem > 0)
	{
		check_if_rotate(l, &print_a, autocomp);
		print_a.condition = print_a.more == 0 ? autocomp->tab_a.size : l->hauteur - 1;
		while (print_a.i < print_a.condition)
		{
			print_a.more = print_a.more == 1 ? 0 : print_a.more;
			print_a.tmp = ARRAY_GETT(t_string, &autocomp->tab_a, print_a.get);
			if (print_a.get < print_a.nb_elem)
				print_elem(&print_a, autocomp);
			else
			{
				autocomp->nl++;
				ft_putstr("\n");
				print_a.nb_elem = print_a.nb_elem + print_a.nb_col;
			}
		}
	}
	ft_home(l);
	do_goto("UP", autocomp->nl + 1, autocomp->nl + 1);
	while (l->cursor < l->sauv_cursor)
	  {
	    do_term("nd");
	    l->cursor++;
	}
//	printf("cursor : %d  sauv: %d\n", l->cursor, autocomp->cursor_tmp);
//	l->sauv_cursor = autocomp->cursor_tmp;
//	printf("cursor : %d  sauv: %d\n", l->cursor, autocomp->cursor_tmp);
/*	while (l->cursor <= l->sauv_cursor + 1)
	{
		do_term("nd");
		l->cursor++;
		}*/
	//l->sauv_cursor = l->str.size;
//	ft_end(l);
}
