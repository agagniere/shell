/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 08:28:57 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/16 16:44:44 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>


t_string		sh_resolve(t_sh_node *self)
{
	t_string	ans[1];
	int			fd[3];
	int			ret;
	char		buff[512];

	*ans = NEW_STRING;
	fd[2] = dup(1);
	if (!pipe(fd))
	{
		dup2(fd[1], 1);
		((t_sh_operator *)self)->exec((t_sh_operator *)self);
		while (0 < (ret = read(fd[0], buff, 512)))
			fta_append(ans, buff, ret);
		dup2(fd[2], 1);
		close(fd[0]);
		close(fd[1]);
	}
	close(fd[2]);
	return (*ans);
}

static int		_exec_rd(t_sh_operator *self, int fd)
{
	t_sh_redirection *const	this = (t_sh_redirection *)self;
	t_sh_operator *const	right = (t_sh_operator *)&self->super.right;
	int						bck;
	int						ans;

	ans = 0;
	bck = dup(this->filedes);
	dup2(fd, this->filedes);
	if (right)
		ans = right->exec(right);
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

	fd = open(ft_string(sh_resolve((t_sh_node *)left)),
			  this->flags, S_IRWXU | S_IROTH);
	return (_exec_rd(self, fd));
}

int				exec_rd(t_sh_operator *self, t_sh_context *w)
{
	t_sh_redirection *const	this = (t_sh_redirection *)self;
	t_sh_operator *const	left = (t_sh_operator *)&self->super.left;
	int						fd;

	fd = ft_atoi(ft_string(sh_resolve((t_sh_node *)left)));
	return (_exec_rd(self, fd));
}
