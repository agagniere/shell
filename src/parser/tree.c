/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/29 01:26:40 by angagnie         ###   ########.fr       */
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
	return (((t_sh_operator *)*a)->push(a, b));
}

/*
** -----------------------------------------------------------------------------
*/

t_tr		shpush_node(t_tnode **self, t_tnode *new)
{
	return (TR_DONE);
}

t_tr		shpush_rdrc(t_tnode **self, t_tnode *new)
{
	if ((*self)->left == NULL)
		;
	return (TR_DONE);
}

t_tr		shpush_list(t_tnode **self, t_tnode *new)
{
	t_sh_list		*const this = (t_sh_list *)(*self);

	fta_append(this->nodes, new, 1);
	return (TR_NONE);
}
