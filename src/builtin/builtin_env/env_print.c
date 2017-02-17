/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 18:26:50 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/17 14:58:13 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_cell(const t_env_cell *cell)
{
	if (!cell)
		return (1);
	ft_putstr(cell->key);
	ft_putstr("=");
	ft_putendl(cell->value);
	return (0);
}

/*
** Instead of
** `env_print(e)`
** one could write
** `fta_iter(&e->tab, &print_cell)`
*/

int		env_print(t_env *env)
{
	void	*iterator;

	iterator = ARRAY_ITERATOR(&env->tab);
	while (ARRAY_HASNEXT(&env->tab, iterator))
		print_cell((t_env_cell *)iterator);
	return (0);
}
