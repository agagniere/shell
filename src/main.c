/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/05 20:46:59 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"

#include <stdio.h> // <--

t_env           g_env;
t_line          g_line;
t_multi         g_multi;
t_history       g_history;

int		main(int ac, char **av)
{
	char*	cmd1 = "echo Hello  World	\\! |cat; man && ls | head & emacs || exit;";
	char*	cmd2 = "{ echo lol | cat -e &> } 2| c`echo 'a'`t -e";
	t_tokenizer tk;
	t_string	str[1];
	*str = NEW_STRING;
	STR_JOIN_CS(str, cmd1, ft_strlen(cmd1));
	t_sis in = NEW_SIS(str);

	tk = NEW_TOKENIZER((t_is *)&in);
	while (!tk.eof)
	{
		if (!sh_tokenize(&tk))
			printf("%s(%.*s, %i)%s\n", PURPLE,
				   tk.current.data.len, tk.current.data.str, tk.current.tag,
				   EOC);
	}
	return (0);
}
