/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 19:50:44 by malaine           #+#    #+#             */
/*   Updated: 2016/05/24 16:51:46 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		putchar_s(int c)
{
	write(2, &c, 1);
	return (1);
}

int		ft_init_term(void)
{
	char				*name_term;
	struct termios		term;

	if ((name_term = getenv("TERM")) == NULL)
	{
		ft_putendl_fd("Env inexistant", 2);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	tputs(tgetstr("ti", NULL), 1, putchar_s);
	tputs(tgetstr("vi", NULL), 1, putchar_s);
	return (0);
}

int		ft_reset_term(void)
{
	struct termios		term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	tputs(tgetstr("te", NULL), 1, putchar_s);
	tputs(tgetstr("ve", NULL), 1, putchar_s);
	tputs(tgetstr("cl", NULL), 1, putchar_s);
	return (0);
}
