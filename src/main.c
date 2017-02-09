/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:54:21 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/09 20:32:03 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env			g_env;
t_line			g_line;

void			print_key(t_line *l)
{
	l->count++;
}

static int		get_input(t_line *line)
{
	
	while (1)
	{
		ft_bzero(READ_BUFFER(line), READ_BUFFER_SIZE);
		if (read(0, READ_BUFFER(line), READ_BUFFER_SIZE) == -1)
			return (1);
		if (READ_BUFFER(line)[0] != '\n')
		{
			actions(line);
		}
		if (READ_BUFFER(line)[0] != '\n'
				&& ft_isprint(READ_BUFFER(line)[0]) == 1)
		{
			print_key(line);
			
		}
		if (READ_BUFFER(line)[0] == '\n')
		{
			//ft_end(line);
			//ft_putchar('\n');
			return (0);
		}
	}
}

static int		start_input(t_line *line)
{
	while (1)
	{
		ft_putstr("$> ");
		if (get_input(line) != 0)
			ft_putendl_fd("error\n", 2);
		//printf("la string: %s\n", STR(line));
	}
}

int				main(int ac, char **av, char **environ)
{
	ac = 0;
	(void)av;
	line_init(&g_line);
	ft_init_term();
	env_init(&g_env, environ);
	start_input(&g_line);
	//env_print(&g_env);

	return (0);
}
