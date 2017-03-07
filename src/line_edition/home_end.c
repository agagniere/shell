/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_home_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 17:35:38 by malaine           #+#    #+#             */
/*   Updated: 2017/03/07 15:52:47 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"


static int count_n_char(char *str, size_t n, char c)
{
	int i;

	i = 0;
	while (*str != '\0' && n--)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

static	void			print_big(t_line *l)
{
	int nb_char;

	nb_char = l->largeur * l->hauteur - SIZE_PROMPT;
	write(1, (char *)l->str.data, nb_char);
}

void			ft_home(t_line *l)
{
	if (l->str.size + SIZE_PROMPT > (l->largeur * l->hauteur) - 1)
	{
		l->nbline = l->largeur * l->hauteur;
		do_term("cl");
		ft_putstr("$> ");
		print_big(l);
	}
	else
		l->nbline = (l->cursor + SIZE_PROMPT) / (l->largeur ? l->largeur : 1);
//	l->nbline += count_n_char((char *)l->str.data, (size_t)l->cursor, '\n');
		do_goto("ch", 0, SIZE_PROMPT);
		if (l->nbline != 0)
			do_goto("UP", l->nbline, l->nbline);
		l->cursor = 0;
}

void			ft_end(t_line *l)
{
	if (l->str.size + SIZE_PROMPT > (l->largeur * l->hauteur) - 1)
    {
		l->cursor = l->str.size;
		ft_ctrl_l(l);
	}
	else
	{
		while (l->cursor < l->str.size)
			go_down(l);
	}
}
