/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/27 22:18:47 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		main(int ac, char **av)
{
	t_tree		ast;
	t_tnode		*new;
	t_sh_leaf	leaf;

	ast = NEW_TREE(t_sh_node);
	leaf = NEW_LEAF("echo");
	new = &leaf;
	ftt_push(ast, new);
	return (0);
}
