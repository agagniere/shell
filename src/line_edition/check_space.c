/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:58:03 by malaine           #+#    #+#             */
/*   Updated: 2017/02/14 17:02:49 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void check_is_space_l(t_line *l)
{
	while (*(char *)ARRAY_GET(&l->str, l->cursor - 1) == ' ')
		go_up(l);
}

void check_space_l(t_line *l)
{
	while (*(char *)ARRAY_GET(&l->str, l->cursor - 1) != ' ' && l->cursor != 0)
		go_up(l);
}

void check_space_r(t_line *l)
{
	while (*(char *)ARRAY_GET(&l->str, l->cursor) != ' ' && *(char *)ARRAY_GET(&l->str, l->cursor) != '\0')
		go_down(l);
}

void check_is_space_r(t_line *l)
{
	while (*(char *)ARRAY_GET(&l->str, l->cursor) == ' ')
		go_down(l);
}
