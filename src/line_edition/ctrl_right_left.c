/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:40:52 by malaine           #+#    #+#             */
/*   Updated: 2017/02/14 16:45:14 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void        ft_ctrl_right(t_line *l)
{
    void    *ite;

    ite = ARRAY_GET(&l->str, l->cursor);

    if (check_last_word(l) == 0)
    {
		if (*(char *)ite == ' ')
            check_is_space_r(l);
		else
		{
            check_space_r(l);
            check_is_space_r(l);
		}
    }
    else
        check_space_r(l);
}

void        ft_ctrl_left(t_line *l)
{
	void    *ite;

    ite = ARRAY_GET(&l->str, l->cursor - 1);

    if (*(char *)ite != ' ')
		check_space_l(l);
    else
    {
		check_is_space_l(l);
		check_space_l(l);
    }
}
