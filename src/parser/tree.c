/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/19 14:10:03 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** shellPush(N**, N*)
*/

t_tr		_leaf_push(t_tnode **a, t_tnode *b)

t_tr		shell_push(t_tnode **a, t_tnode *b)
{
	if (!ASSERT(b != NULL))
		return (TR_NONE);
	if (*a == NULL && (*a = b))
		return (TR_DONE);
	if (NODE_ISLEAF(*a))
		return (_leaf_push(a, b));

	return (TR_ERROR);
}
