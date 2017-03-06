/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 14:25:24 by malaine           #+#    #+#             */
/*   Updated: 2017/03/03 15:11:56 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <curses.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <term.h>
#include <unistd.h>

int			int_putchar(int c)
{
	write(2, &c, 1);
	return (0);
}

int			do_goto(char *key, int col, int row)
{
	char	*ret;

	if ((ret = tgetstr(key, NULL)) == NULL)
		return (1);
	ret = tgoto(ret, col, row);
	tputs(ret, 0, int_putchar);
	return (0);
}

int			do_term(char *key)
{
	char	*ret;

	if ((ret = tgetstr(key, NULL)) == NULL)
		return (1);
	tputs(ret, 0, int_putchar);
	return (0);
}
