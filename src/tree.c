/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:58:37 by angagnie          #+#    #+#             */
/*   Updated: 2017/02/10 00:26:49 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Fails if both _a_ and _b_ are leaves.
*/

int		shell_push(t_node **a, t_node *b)
{
	const t_shell_node *ac = (t_shell_node *)*a;
	const t_shell_node *bc = (t_shell_node *)b;

	if (*a == NULL)
	{
		*a = b;
		return (0);
	}
	if (!*a->is_node && !b->is_node)
		return (-1);
	else if (!b->is_node || PRECEDENCE(ac->name) >= PRECEDENCE(bc->name))
		return (2);
	else if (!a->is_node || PRECEDENCE(a->name) < PRECEDENCE(b->name))
	{
		b->left = *a;
		*a = b;
		return (0);
	}
	else
		return (-1);
}
