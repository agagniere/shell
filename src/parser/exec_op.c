/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:33:28 by angagnie          #+#    #+#             */
/*   Updated: 2020/10/04 01:00:01 by sid              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_printf.h"

/*
** Those functions return 0 upon successful completion.
*/

int		exec_semi(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)self->super.left;
	t_sh_operator *const right = (t_sh_operator *)self->super.right;


	ft_dprintf(2, "$s(%p)\n", __FUNCTION__, self);
	return ((left && left->exec(left, w) && !right)
			|| (right && right->exec(right, w)));
}

int		exec_amper(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)self->super.left;
	t_sh_operator *const right = (t_sh_operator *)self->super.right;

	ft_dprintf(2, "$s(%p)\n", __FUNCTION__, self);
	if (left && !fork())
	{
		left->exec(left, w);
		_Exit(0);
	}
	return (right && right->exec(left, w));
}

int		exec_andif(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)self->super.left;
	t_sh_operator *const right = (t_sh_operator *)self->super.right;

	ft_dprintf(2, "$s(%p)\n", __FUNCTION__, self);
	return (left->exec(left, w) ? 1 : right && right->exec(right, w));
}

int		exec_orif(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const left = (t_sh_operator *)self->super.left;
	t_sh_operator *const right = (t_sh_operator *)self->super.right;

	ft_dprintf(2, "$s(%p)\n", __FUNCTION__, self);
	return (left->exec(left, w) ? right && right->exec(right, w) : 0);
}

int		exec_pipe(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const	left = (t_sh_operator *)self->super.left;
	t_sh_operator *const	right = (t_sh_operator *)self->super.right;
	int						backup[2];
	int						pipe_fds[2];
	int						ans = 0;

	ft_dprintf(2, "$s(%p)\n", __FUNCTION__, self);
	backup[STDIN_FILENO] = dup(STDIN_FILENO);
	backup[STDOUT_FILENO] = dup(STDOUT_FILENO);
	pipe(pipe_fds);
	dup2(pipe_fds[STDOUT_FILENO], STDOUT_FILENO);
	dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO);
	if (fork() == 0 /* Child */)
	{
		left->exec(left, w);
		_Exit(0);
	}
	else
		ans = right->exec(right, w);
	dup2(backup[STDIN_FILENO], STDIN_FILENO);
	dup2(backup[STDOUT_FILENO], STDOUT_FILENO);
	close(backup[STDIN_FILENO]);
	close(backup[STDOUT_FILENO]);
	close(pipe_fds[STDIN_FILENO]);
	close(pipe_fds[STDOUT_FILENO]);
	return (ans);
}
