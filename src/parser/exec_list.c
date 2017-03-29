/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:40:23 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/29 01:24:31 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			exec_list(t_sh_operator *self, t_sh_context *w)
{
	t_sh_list		*this = (t_sh_list *)self;
	void			*ite;
	t_string		str[1];
	t_array			argv[1];

	*argv = NEW_ARRAY(char *);
	ite = ARRAY_ITERATOR(this->nodes);
	while (ARRAY_HASNEXT(this->nodes, ite))
	{
		if (NODE_ISLEAF(ite))
		{
			fta_append(argv, ARRAY_END(str), 1);
			fta_append(str, ((t_sh_leaf *)ite)->str.str,
					   ((t_sh_leaf *)ite)->str.len);
			fta_append(str, "", 1);
		}
		else
			sh_resolve((t_sh_node *)ite, w);

	}
	return (0);
}
