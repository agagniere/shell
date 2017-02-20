/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_up_down_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 10:52:44 by malaine           #+#    #+#             */
/*   Updated: 2017/02/14 16:33:33 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void		go_up(t_line *l)
{
	if (l->largeur != 0 && ((l->cursor + SIZE_PROMPT) % l->largeur) == 0)
	{
		do_term("up");
		do_goto("ch", 0, l->largeur - 1);
	}
	else
		do_term("le");
	l->cursor--;
}

void		go_down(t_line *l)
{
	l->cursor++;
	if (l->largeur != 0 && ((l->cursor + SIZE_PROMPT) % l->largeur) == 0)
		do_term("do");
	else
		do_term("nd");
}
