/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/22 13:00:30 by angagnie         ###   ########.fr       */
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
** shell push
** -
** _a_ and _b_ must not be NULL,
** but *_a_ can be.
** -
** _b_ is the node pushed.
** -
** returns a TR status :
** left, right, done, none or error.
** (never both)
*/

t_tr		shell_push(t_tnode **a, t_tnode *b)
{
	if (b == NULL)
		return (TR_NONE);
	if (*a == NULL && (*a = b))
		return (TR_DONE);
	if (NODE_ISLEAF(*a))
		return (_push(a, b));
	return (((t_sh_operator *)*a)->push(a, b));
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

	if (NODE_ISLEAF(new))
	{
		fta_append(this->nodes, new, 1);
		return (TR_NONE);
	}
	return (_push(self, new));
}
