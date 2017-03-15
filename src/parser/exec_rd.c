/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 08:28:57 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/15 11:50:27 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		exec_rdf(t_sh_operator *self, t_sh_context *w)
{
	t_sh_redirection *const	this = self;
	t_sh_operator *const	left = (t_sh_operator *)&self->super.left;
	t_sh_operator *const	right = (t_sh_operator *)&self->super.right;
	int		fd;
	int		bck;
	int		ans;

	ans = 0;
	fd = openat(resolve(ft_string(left), ft_pwd(w), this->flags));
	bck = dup(this->filedes);
	dup2(fd, this->filedes);
	if (right)
		ans = right.exec(right);
	dup2(bck, filedes);
	close(bck);
	close(fd);
	return (ans);
}

int		tmp()
{
	t_tree ast[1];

	*ast = NEW_TREE(union u_sh_node);
	ftt_push(ast, NEW_NODE(SH_PIPE));
}
