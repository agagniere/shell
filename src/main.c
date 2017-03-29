/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/29 05:32:13 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		main(int ac, char **av)
{
	t_tree		ast[1];
	t_tnode		*new;
	t_sh_leaf	leaf;
	t_sh_list	list;
	t_sh_node	node;

	*ast = NEW_TREE(t_sh_node, &shell_push);
	leaf = NEW_LEAF(NEW_SUB("echo"));
	list = NEW_SHLIST;
	node.leaf = leaf;
	fta_append(list.nodes, &node, 1);
	node.list = list;
	new = (t_tnode *)&list; ftt_push(ast, new);
	ftt_debug(ast);
	return (0);
}
