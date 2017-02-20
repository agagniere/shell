/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_up_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:22:44 by jguthert          #+#    #+#             */
/*   Updated: 2017/02/20 18:28:15 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void		ft_ctrl_up(t_line *l)
{
	if ((int)l->cursor >= l->largeur)
	{
		do_term("up");
		l->cursor = l->cursor - l->largeur;
	}
	else
		ft_home(l);
}

void		ft_boucle_down(int i, int z, t_line *l)
{
	while (z < i)
	{
		do_term("nd");
		l->cursor++;
		z++;
	}
}

void		ft_first_line_down(t_line *l)
{
	int i;

	i = l->cursor + SIZE_PROMPT;
	l->cursor = l->largeur - SIZE_PROMPT;
	if (l->cursor + i <= l->str.size)
		ft_boucle_down(i, 0, l);
	else
		ft_boucle_down(l->str.size, l->cursor, l);
}

void		ft_other_line_down(t_line *l)
{
	int i;
	int z;

	i = (l->cursor + SIZE_PROMPT) / l->largeur;
	z = l->cursor - i * l->largeur + SIZE_PROMPT;
	l->cursor = l->cursor + l->largeur - z;
	ft_boucle_down(z, 0, l);
}

void		ft_ctrl_down(t_line *l)
{
	if ((int)l->cursor + l->largeur < (int)l->str.size)
	{
		do_term("do");
		if ((int)l->cursor < l->largeur - SIZE_PROMPT)
			ft_first_line_down(l);
		else
			ft_other_line_down(l);
	}
	else
		ft_end(l);
}
