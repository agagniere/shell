/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:33:28 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/24 22:22:33 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Those functions return 0 upon successful completion.
*/

int		exec_semi(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const right = (t_sh_operator *)&self->super.right;

	return ((left && left->exec(left, w) && !right)
			|| (right && right->exec(right, w)));
}

int		exec_amper(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const right = (t_sh_operator *)&self->super.right;

	if (!fork() && left)
	{
		left->exec(left, w);
		_Exit(0);
	}
	return (right && right->exec(left, w));
}

int		exec_andif(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const right = (t_sh_operator *)&self->super.right;

	return (left->exec(left, w) ? 1 : right && right->exec(right, w));
}

int		exec_orif(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const right = (t_sh_operator *)&self->super.right;

	return (left->exec(left, w) ? right && right->exec(right, w) : 0);
}

int		exec_pipe(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const	left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const	right = (t_sh_operator *)&self->super.right;
	int						bck[2];
	int						p[2];
	int						ans;

	bck[0] = dup(0);
	bck[1] = dup(1);
	pipe(p);
	dup2(p[1], 1);
	dup2(p[0], 0);
	if ((ans = 0) || !fork())
	{
		left->exec(left, w);
		_Exit(0);
	}
	else
		ans = right->exec(right, w);
	dup2(bck[0], 0);
	dup2(bck[1], 1);
	close(bck[0]);
	close(bck[1]);
	close(p[0]);
	close(p[1]);
	return (ans);
}
