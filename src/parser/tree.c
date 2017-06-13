/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/06/13 15:39:57 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tr	_push(t_tnode **a, t_tnode *b)
{
	b->left = *a;
	*a = b;
	return (TR_DONE);
}

/*
** -----------------------------------------------------------------------------
*/

t_tr		shpush_node(t_tnode **self, t_tnode *new)
{
	if (NODE_PRECEDENCE(new) < NODE_PRECEDENCE(*self))
		return (_push(self, new));
	return (TR_RIGHT);
}

t_tr		shpush_rdrc(t_tnode **self, t_tnode *new)
{
	if ((*self)->left == NULL)
	{
		(*self)->left = new;
 		return (TR_DONE);
	}
	else
		return (TR_RIGHT);
}

t_tr		shpush_list(t_tnode **self, t_tnode *new)
{
	t_sh_list		*const this = (t_sh_list *)(*self);

	dprintf(2, "List::push\n");
	if (new->label & 0x80)
		return (_push(self, new));
	fta_append(this->nodes, new, 1);
	return (TR_DONE);
}

t_tr		shpush_leaf(t_tnode **self, t_tnode *new)
{
	t_sh_node	*node;

	dprintf(2, "Leaf::push\n");
	if (new->label & 0x80)
		return (_push(self, new));
	if (node = (t_sh_node *)malloc(sizeof(t_sh_node)))
		exit(1);
	node->list = NEW_SHLIST;
	node->op.push((t_tnode **)&node, *self);
	node->op.push((t_tnode **)&node, new);
	*self = node;
	return (TR_NONE);
}
