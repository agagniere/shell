/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 04:24:35 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/30 17:49:06 by angagnie         ###   ########.fr       */
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
	t_tree		ast[1];
	t_sh_node	node;
	t_sh_list	list;

	*ast = NEW_TREE(t_sh_node, &shell_push);
	list = NEW_SHLIST;

	node.leaf = NEW_LEAF(NEW_SUB("echo")); fta_append(list.nodes, (void *[1]){&node}, 1);
	printf("%p ?= %p\n", &node, ARRAY_GETL(void *, list.nodes, 0));
	ftt_push(ast, (t_tnode *)&list);
	node.leaf = NEW_LEAF(NEW_SUB("Hello")); ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("World")); ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("!")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_PIPE; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("cat")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_SEMI; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("man")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_AND_IF; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("ls")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_PIPE; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("head")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_AMPER; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("emacs")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_OR_IF; ftt_push(ast, (t_tnode *)&node);
	node.leaf = NEW_LEAF(NEW_SUB("exit")); ftt_push(ast, (t_tnode *)&node);
	node.op = OP_SEMI; ftt_push(ast, (t_tnode *)&node);

	ftt_debug(ast);

	((t_sh_operator *)ast->root)->exec((t_sh_operator *)ast->root, NULL);
	return (0);
}
