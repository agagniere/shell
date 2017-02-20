/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:00:52 by malaine           #+#    #+#             */
/*   Updated: 2017/02/14 16:54:57 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

int		check_last_word(t_line *l)
{
	int a;
	void    *ite;

    ite = ARRAY_GET(&l->str, l->cursor);
	a = l->cursor;
	while (ARRAY_HASNEXT(&l->str, ite))
    {
		if (*(char *)ite == ' ' || *(char *)ite == '\t')
			return (0);
	}
	return (-1);
}

int		check_first_word(t_line *l)
{
	int a;

	a = l->cursor;
	while (a >= 0)
	{
		if (*(char *)ARRAY_GET(&l->str, a) == ' ' || *(char *)ARRAY_GET(&l->str, a) == '\t')
			return (0);
		a--;
	}
	return (-1);
}
