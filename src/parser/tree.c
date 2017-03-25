/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/25 06:08:03 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	if (*a == NULL && (*a = b))
		return (TR_DONE);
	return ((*a)->push(a, b));
}

/*
** -----------------------------------------------------------------------------
*/

t_tr		shpush_node(t_tnode **self, t_tnode *new)
{
	(*self)->
	return ();
}

t_tr		shpush_rdrc(t_tnode **self, t_tnode *new)
{
	if ((*self)->left == NULL)
		;
	return ();
}

t_tr		shpush_list(t_tnode **self, t_tnode *new)
{
	t_sh_list		*const this = (t_sh_list *)(*self);

	fta_append(this->nodes, new);
	return (TR_NONE);
}
