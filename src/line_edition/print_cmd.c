/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 16:59:38 by jguthert          #+#    #+#             */
/*   Updated: 2017/03/07 17:36:45 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "shell.h"

static void	print_str(t_line *l)
{
	void    *ite;

	ite = ARRAY_GET(&l->str, l->cursor - 1);
	while (ARRAY_HASNEXT(&l->str, ite))
	{
		ft_putchar(*(char *)ite);
		l->cursor++;
		if (l->largeur != 0 &&
			((l->cursor + SIZE_PROMPT) % l->largeur) == 0)
			do_term("do");
	}
}

void	put_cursor(t_line *l)
{
	if (l->sauv_cursor <= (int)l->str.size / 2)
	{
		ft_home(l);
		while ((int)l->cursor < l->sauv_cursor)
			ft_right(l);
	}
	else
		while ((int)l->cursor > l->sauv_cursor)
			ft_left(l);
}

void		print(t_line *l)
{
	do_term("cd");
	print_str(l);
	put_cursor(l);
}
