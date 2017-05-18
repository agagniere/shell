/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/18 13:50:36 by angagnie         ###   ########.fr       */
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
	char*	cmd0 = "<<<;>>|&>|&&&&|||>>>|<<< <<-<>>&<&|&&>";
	char*	cmd1 = "echo Hello	  World' !' |cat;man&&ls|head&emacs||exit;";
	char*	cmd2 = "{echo lol|cat -e&>}2|c`echo 'a'`t -e";
	char*	cmd3 = "echo \"\"  \"-`echo 'Hello '\\`echo \"World \# \! !1 \"\\``-\"";
	char*	cmd4 = "ls|echo \\!\"Teext`echo Damn`\"";

	t_string	str[1];
	*str = NEW_STRING;
	STR_JOIN_CS(str, cmd0, ft_strlen(cmd4));

	ft_antoine(str);
	return (0);
}
