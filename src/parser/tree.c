/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/09 16:04:47 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** shellPush
** -
** Fails if both _a_ and _b_ are leaves.
*/

t_tr		shell_push(t_node **a, t_node *b)
{
	const t_shell_node *ac = (t_shell_node *)*a;
	const t_shell_node *bc = (t_shell_node *)b;

	if (ac == NULL)
	{
		*a = b;
		return (TR_DONE);
	}
	if (NODE_ISLEAF(*a) && NODE_ISLEAF(b))
		return (TR_ERROR);
	else if (NODE_ISLEAF(b) || PRECEDENCE(ac->name) >= PRECEDENCE(bc->name))
		return (TR_RIGHT);
	else if (!a->is_node || PRECEDENCE(ac->name) < PRECEDENCE(bc->name))
	{
		b->left = *a;
		*a = b;
		return (TR_DONE);
	}
	return (TR_ERROR);
}
