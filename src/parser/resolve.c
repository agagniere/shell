/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 23:49:42 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/18 23:50:37 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

t_string		sh_resolve(t_sh_node *self, t_sh_context *w)
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
		((t_sh_operator *)self)->exec((t_sh_operator *)self, w);
		while (0 < (ret = read(fd[0], buff, 512)))
			fta_append(ans, buff, ret);
		dup2(fd[2], 1);
		close(fd[0]);
		close(fd[1]);
	}
	close(fd[2]);
	return (*ans);
}
