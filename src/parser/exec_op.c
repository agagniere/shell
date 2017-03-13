/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:33:28 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/13 23:57:32 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

/*
** Those functions return 0 upon successful completion.
*/

int		exec_semi(t_sh_operator *self)
{
	t_sh_operator *const left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const right = (t_sh_operator *)&self->super.right;

	return (
		(left && left->exec(left))
		|| (right && right->exec(right)));
}

int		exec_amper(t_sh_operator *self)
{
	t_sh_operator *const left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const right = (t_sh_operator *)&self->super.right;

	if (!fork() && left)
	{
		left.exec(left);
		_Exit(0);
	}
	return (left && left->exec(left));
}

int	exec_andif(t_sh_operator *self)
{

}
