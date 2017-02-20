/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:29:42 by malaine           #+#    #+#             */
/*   Updated: 2017/02/14 17:48:25 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "multi_line.h"

void	multi_tab(t_multi *multi)
{
	multi->pos_rtn = NEW_ARRAY(int);
	multi->size_str = NEW_ARRAY(int);
	multi->index1 = 0;
	multi->index2 = 0;
	multi->index3 = 0;
}

int		multi_init(t_multi *multi)
{
	if (multi == NULL)
		return (1);
	multi_tab(multi);
	return (0);
}
