/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 18:26:50 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/13 19:39:59 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_cell(t_env_cell *const cell)
{
	if (!cell)
		return (1);
	ft_putstr(cell->key);
	ft_putstr("=");
	ft_putendl(cell->value);
	return (0);
}

int		env_print(t_env *env)
{
	t_env_cell **const	tab = env->tab.data;
	size_t				i;

	i = 0;
	while (i < env->tab.size)
	{
		print_cell(tab[i]);
		i++;
	}
	return (0);
}
