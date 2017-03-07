/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:54:21 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/07 17:30:56 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>
#include "edit_line.h"

t_env			g_env;
t_line			g_line;
t_multi			g_multi;
t_history		g_history;

void			winsize()
{
	struct winsize		w;

	ioctl(0, TIOCGWINSZ, &w);
	g_line.largeur = w.ws_col;
	g_line.hauteur = w.ws_row;
}


int     ft_is_print(int c)
{
    if (c == 10 || (c >= ' ' && c <= '~'))
	       return (1);
	else
		return (0);
}

int			ft_replace_accent(char c)
{
	if ((c >= 0 && c != 10  && c <= 27) || c == 127)
		return (666);
	else if (c <= -91 && c >= -96)
		return ('a');
	else if (c <= -85 && c >= -88)
		return ('e');
	else if (c <= -84 && c >= -81)
		return ('i');
	else if (c <= -74 && c >= -78)
		return ('o');
	else if (c <= -68 && c >= -71)
		return ('u');
	else if (c == 10 || (' ' <= c && c <= '~'))
		return (c);
	else
		return (-61);
}

void			stock_str(t_line *l, char c)
{
	c = ft_replace_accent(c);
	if (c != -61)
	{
		if (STR_INSERT_CS(&l->str, &c, 1, l->cursor))
			printf("Fail\n");
		l->sauv_cursor = l->cursor + 1;
		print(l);
	}
}

int			gestion_buffer(t_line *l)
{
	int a;

	a = -1;
	if (l->sauv != NULL)
	{
		while (l->sauv[++a] != '\0')
		{
			if (l->sauv[a] == '\n')
			{
				if (++a <= 5)
					l->sauv = ft_strjoin(ft_strdup(l->sauv + a), l->buffer);
				return (0);
			}
			stock_str(l, l->sauv[a]);
		}
		l->sauv = NULL;
 	}
	a = -1;
	while (l->buffer[++a] != '\0' && l->buffer[a] != '\n')
		stock_str(l, l->buffer[a]);
	if (l->buffer[a] != '\n')
		return (1);
	else if (++a <=5)
		l->sauv = ft_strdup(l->buffer + a);
	return (0);
}


void			reset_line(t_line *l)
{
	g_history.first_time = 0;
	if (l->str.size > 0)
		bi_history_save(&g_history, &l->str);
	l->str.size = 0;
	l->cursor = 0;
    ft_putstr("\n$> ");

}


static void is_sig(int signum)
{
//	ft_putnbr(signum);
	if (signum == SIGINT)
	{
		ft_end(&g_line);
		do_term("cd");
		g_line.str.size = 0;
		reset_line(&g_line);
	}
	if (signum == SIGWINCH)
	{
		winsize();
		ft_ctrl_l(&g_line);
	}
}

void catch_signal(void)
{
	int i;

	i = 0;
	while (i++ < 28)
		signal(i, is_sig);
}

static int		get_input(t_line *l)
{
	while (1)
	{
		ft_bzero(READ_BUFFER(l), 7);
		while (l->sauv != NULL)
			if (gestion_buffer(l) == 0)
				return (0);
		if (read(0, READ_BUFFER(l), READ_BUFFER_SIZE) == -1)
			return (1);
		if (READ_BUFFER(l)[0] != '\n')
			actions(l);
		if (ft_replace_accent(l->buffer[0]) != 666)
			if (gestion_buffer(l) == 0)
			{
				do_term("cd");
				return (0);
			}
	}
}

static int		start_input(t_line *l)
{
	l->sauv = NULL;
	while (1)
	{
		reset_line(l);
		catch_signal();
		if (get_input(l) != 0)
			ft_putendl_fd("error\n", 2);
	}
}

int				main(int ac, char **av, char **environ)
{
    ac = 0;
    (void)av;
    winsize();
    line_init(&g_line);
    ft_init_term();
	bi_history_init(&g_history);
    env_init(&g_env, environ);
    multi_init(&g_multi);
    start_input(&g_line);
	return (0);
}
