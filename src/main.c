/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/04/11 18:29:32 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
# include "shell.h"

t_env           g_env;
t_line          g_line;
t_multi         g_multi;
t_history       g_history;

int		main(int ac, char **av)
{
	char*	cmd = "echo Hello  World	\\! |cat; man && ls | head & emacs || exit;",
		cmd2 = "{ echo lol | cat -e &> } 2| c`echo 'a'`t -e";


	return (0);
}
