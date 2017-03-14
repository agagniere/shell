/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 08:28:57 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/14 10:28:48 by angagnie         ###   ########.fr       */
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

	fd = openat(resolve(ft_string(left), ft_pwd(w), this->flags));
	in = dup(this->filedes);
	dup2(fd, filedes);
	if ()
}
