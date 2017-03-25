/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/25 03:39:03 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tr		shell_push(t_tnode **a, t_tnode *b)
{
	if (*a == NULL)
	{
		if (b == NULL)
			return (TR_ERROR);
		*a = b;
		return (TR_DONE);
	}
	return ((*a)->push(a, b));
}

t_tr		shpush_node(t_tnode **self, t_tnode *new)
{
	(*self)->
	return ();
}

t_tr		shrdrc_node(t_tnode **self, t_tnode *new)
{
	if ((*self)->left == NULL)
		;
	return ();
}

t_tr		shlist_node(t_tnode **self, t_tnode *new)
{

	return ();
}
