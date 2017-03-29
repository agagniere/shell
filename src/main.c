/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/29 08:20:16 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		main(int ac, char **av)
{
	t_tree		ast[1];
	t_sh_node	node;

	*ast = NEW_TREE(t_sh_node, &shell_push);

	node.leaf = NEW_LEAF(NEW_SUB("A echo")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_PIPE; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("B cat")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_SEMI; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("C man")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_AND_IF; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("D ls")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_PIPE; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("E head")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_AMPER; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("E emacs")); ftt_push(ast, (t_tnode *)&node);

	ftt_debug(ast);
	ftt_debug(ast);
	((t_sh_operator *)ast->root)->exec(ast->root, NULL);
	return (0);
}
