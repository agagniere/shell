/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 18:26:50 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/20 19:05:32 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		print_cell(const void *ptr)
{
	const t_env_cell	*cell = ptr;

	if (cell)
	{
		ft_putstr(cell->key);
		ft_putstr("=");
		ft_putendl(cell->value);
	}
}

/*
** Instead of
** `env_print(e)`
** one could write
** `fta_iter(&e->tab, &print_cell)`
*/

int		env_print(t_env *env)
{
	fta_iter(&env->tab, &print_cell);
	return (0);
}
