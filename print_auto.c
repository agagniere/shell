/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:02:52 by malaine           #+#    #+#             */
/*   Updated: 2017/03/03 17:17:16 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <term.h>
#include <unistd.h>
#include <string.h>
#include "libft/include/libft.h"

int     putchar_s(int c)
{
    write(2, &c, 1);
    return (1);
}

int     ft_init_term(void)
{
    char                *name_term;
    struct termios      term;

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
    return (0);
}

int     ft_reset_term(void)
{
    struct termios      term;

    if (tcgetattr(0, &term) == -1)
        return (-1);
    term.c_lflag |= (ICANON | ECHO);
    if (tcsetattr(0, 0, &term) == -1)
        return (-1);
//    tputs(tgetstr("te", NULL), 1, putchar_s);
	//   tputs(tgetstr("ve", NULL), 1, putchar_s);
//    tputs(tgetstr("cl", NULL), 1, putchar_s);
    return (0);
}


int         int_putchar(int c)
{
    write(2, &c, 1);
    return (0);
}

int         do_goto(char *key, int col, int row)
{
    char    *ret;

    if ((ret = tgetstr(key, NULL)) == NULL)
        return (1);
    ret = tgoto(ret, col, row);
    tputs(ret, 0, int_putchar);
    return (0);
}

int         do_term(char *key)
{
    char    *ret;

    if ((ret = tgetstr(key, NULL)) == NULL)
        return (1);
    tputs(ret, 0, int_putchar);
    return (0);
}

int			check_longer(char **possibility)
{
	int max = 0;
	int i = 0;

	while (i < 5)
	{
		if (ft_strlen(possibility[i]) > max)
			max = ft_strlen(possibility[i]);
		i++;
	}
	return (max);
}

void		print_auto(int largeur, int index, char **possibility, int *type)
{
	int i = 0;
	int space;
	int max_name = check_longer(possibility);
	int col_sauv = largeur / (max_name + 2);
	int col = col_sauv;

	while (i < 5)
	{
		if (i < col)
		{
			if (i == index)
				do_term("mr");
			if (type[i] == 1)
				ft_putstr("\033[31m");
			if (type[i] == 2)
				ft_putstr("\033[32m");
			ft_putstr(possibility[i]);
			space = max_name - ft_strlen(possibility[i]);
			while (space-- >= 0)
				ft_putstr(" ");
			do_term("me");
			ft_putstr("  ");
			i++;
		}
		else
		{
			ft_putstr("\n");
			col = col + col_sauv;
		}
	}
	ft_putstr("\n");
}

int			main(void)
{
	ft_init_term();
	char *possibility[5] = {"toto\0", "titi\0", "tutu\0", "maxime\0", "jacky\0"};
	int type[5] ={0, 1, 0, 1, 2}; 
	print_auto(100, 2, possibility, type);
	ft_reset_term();
	return (0);
}
