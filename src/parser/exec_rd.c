/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 08:28:57 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/16 14:19:56 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>
#include "ft_printf.h"

static int		_exec_rd(t_sh_operator *self, int fd, t_sh_context *w)
{
	t_sh_redirection *const	this = (t_sh_redirection *)self;
	t_sh_operator *const	right = (t_sh_operator *)&self->super.right;
	int						bck;
	int						ans;

	ans = 0;
	bck = dup(this->filedes);
	dup2(fd, this->filedes);
	if (right)
		ans = right->exec(right, w);
	dup2(bck, this->filedes);
	close(bck);
	close(fd);
	return (ans);
}

int				exec_rdf(t_sh_operator *self, t_sh_context *w)
{
	t_sh_redirection *const	this = (t_sh_redirection *)self;
	t_sh_operator *const	left = (t_sh_operator *)&self->super.left;
	int						fd;
	t_string				tmp;

	ft_dprintf(2, "%s(%p)\n", __FUNCTION__, self);
	tmp = sh_resolve((t_sh_node *)left, w);
	fd = open(ft_string(&tmp), this->flags, S_IRWXU | S_IROTH);
	return (_exec_rd(self, fd, w));
}

int				exec_rd(t_sh_operator *self, t_sh_context *w)
{
	t_sh_operator *const	left = (t_sh_operator *)&self->super.left;
	int						fd;
	t_string				tmp;

	ft_dprintf(2, "%s(%p)\n", __FUNCTION__, self);
	tmp = sh_resolve((t_sh_node *)left, w);
	fd = ft_atoi(ft_string(&tmp));
	return (_exec_rd(self, fd, w));
}
