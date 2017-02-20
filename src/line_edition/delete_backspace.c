/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_backspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:31:12 by malaine           #+#    #+#             */
/*   Updated: 2017/02/20 18:31:30 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "shell.h"

void        ft_delete(t_line *l)
{
    l->sauv_cursor = l->cursor - 1;
    fta_popindex(&l->str, l->cursor - 1, 1);
    ft_left(l);
    do_term("cd");
    print(l);
}

void        ft_backspace(t_line *l)
{
    l->sauv_cursor = l->cursor;
    fta_popindex(&l->str, l->cursor, 1);
    print(l);
}
