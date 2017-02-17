/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 16:59:38 by jguthert          #+#    #+#             */
/*   Updated: 2017/02/13 18:35:19 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "shell.h"

static void	print_str(t_line *l)
{
	int a;
	void    *ite;

    ite = ARRAY_GET(&l->str, -1);
	a = l->cursor;
	while (ARRAY_HASNEXT(&l->str, ite))
	{
		ft_putchar(*(char *)ite);
		if (l->largeur != 0 && l->cursor != 0
			&& (l->cursor + SIZE_PROMPT + 1) % l->largeur == 0)
			do_term("do");
		l->cursor++;
	}
}

static void	put_cursor(t_line *l)
{
	while ((int)l->cursor < l->sauv_cursor)
	{
		if (l->largeur != 0 && l->cursor != 0
			&& (l->cursor + SIZE_PROMPT + 1) % l->largeur == 0)
			do_term("do");
		else
			do_term("nd");
		l->cursor++;
	}
}

static void	little_print(t_line *l)
{
	ft_home(l);
	do_term("cd");
	print_str(l);
	ft_home(l);
	put_cursor(l);
}

void		print(t_line *l)
{
	little_print(l);
}
