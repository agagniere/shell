/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:40:23 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/25 11:16:08 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_printf.h"

int			exec_list(t_sh_operator *self, t_sh_context *w)
{
	t_sh_list		*this = (t_sh_list *)self;
	void			*ite;
	t_string		str[1];
	t_array			argv[1];

	ft_dprintf(2, "%s(%p)\n", __FUNCTION__, self);
	*argv = NEW_ARRAY(char *);
	ite = ARRAY_ITERATOR(this->nodes);
	while (ARRAY_HASNEXT(this->nodes, ite))
	{
		if (!SH_IS_FLEAF(((t_tnode *)ite)->label))
			sh_resolve((t_sh_node *)ite, w);
		fta_append(argv, ARRAY_END(str), 1);
		fta_append(str, ((t_sh_leaf *)ite)->str.str,
				((t_sh_leaf *)ite)->str.len);
		fta_append(str, "", 1);
	}
	// TODO : Fork
	execv((const char *)ARRAY_GET(argv, 0), (char **)argv->data);
	return (0);
}

int			exec_leaf(t_sh_operator *self, t_sh_context *w)
{
	const char *av[2] = {((t_sh_leaf *)self)->str.str};

	// TODO : Fork
	execv(av[0], av);
	return (0);
}
