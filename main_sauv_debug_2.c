/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:54:21 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/16 15:23:51 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>
#include "edit_line.h"

t_env			g_env;
t_line			g_line;
t_multi			g_multi;

void			winsize()
{
	struct winsize		w;

	ioctl(0, TIOCGWINSZ, &w);
	g_line.largeur = w.ws_col;
	g_line.hauteur = w.ws_row;
}

void			stock_str(t_line *l, char c)
{
	if (STR_INSERT_CS(&l->str, &c, 1, l->cursor))
		printf("Fail\n");
	l->sauv_cursor = l->cursor + 1;
	print(l);
//	check_rtn(l);

}

int			gestion_buffer(t_line *line)
{
	int a;

	a = -1;
	if (line->sauv != NULL)
	{
		while (line->sauv[++a] != '\0')
		{
			if (line->sauv[a] == '\n')
			{
				if (++a <= 5)
					line->sauv = ft_strjoin(ft_strdup(line->sauv + a), line->buffer);
				return (0);
			}
			stock_str(line, line->sauv[a]);
		}
		line->sauv = NULL;
	}
	a = -1;
	while (line->buffer[++a] != '\0' && line->buffer[a] != '\n')
		stock_str(line, line->buffer[a]);
	if (line->buffer[a] != '\n')
		return (1);
	else if (++a <=5)
		line->sauv = ft_strdup(line->buffer + a);
	return (0);

/*	while (line->buffer[++a] != '\0')
	{
		if (line->buffer[a] == '\n')
		{
			if (++a <= 5)
				line->sauv = ft_strdup(line->buffer + a);
			return (0);
		}
		stock_str(line, line->buffer[a]);
	}
	return (1);*/
}

int     ft_isprint_2(int c)
{
    if (c == 10)
        return (1);
    else
        return (' ' <= c && c <= '~');
}


static int		get_input(t_line *line)
{
	while (1)
	{
		ft_bzero(READ_BUFFER(line), 7);
		while (line->sauv != NULL)
			if (gestion_buffer(line) == 0)
				return (0);
		if (read(0, READ_BUFFER(line), READ_BUFFER_SIZE) == -1)
			return (1);
		if (READ_BUFFER(line)[0] != '\n')
			actions(line);
		if (ft_isprint_2(READ_BUFFER(line)[0]) == 1)
			if (gestion_buffer(line) == 0)
				return (0);
	}
}

static int		start_input(t_line *line)
{
	line->sauv = NULL;
	while (1)
	{
		line->str.size = 0;
		line->cursor = 0;
		ft_putstr("\n$> ");
		if (get_input(line) != 0)
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
	env_init(&g_env, environ);
	multi_init(&g_multi);
	start_input(&g_line);
	return (0);
}
