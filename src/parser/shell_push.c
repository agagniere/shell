/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:19:48 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/23 21:57:54 by angagnie         ###   ########.fr       */
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
	if (b == NULL)
		return (TR_NONE);
	if (*a == NULL && (*a = b))
		return (TR_DONE);
	return (((t_sh_operator *)*a)->push(a, b));
}
