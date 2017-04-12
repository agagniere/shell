/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/04/12 16:17:38 by angagnie         ###   ########.fr       */
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
	char*	cmd1 = "echo Hello  World	\\! |cat; man && ls | head & emacs || exit;";
	char*	cmd2 = "{ echo lol | cat -e &> } 2| c`echo 'a'`t -e";
	t_string	cmd[1];
	t_tokenizer tk;
	*cmd = NEW_STRING;
	STR_JOIN_CS(cmd, cmd1, ft_strlen(cmd1));
	t_sis in = NEW_SIS(cmd);

	tk = NEW_TOKENIZER((t_is *)&in);
	while (!tk.eof)
	{
		sh_tokenize(&tk);
		printf("(%s, %i)\n", tk.current.data.str, tk.current.tag);
	}
	return (0);
}
