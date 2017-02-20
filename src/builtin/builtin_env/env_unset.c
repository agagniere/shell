/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:53:22 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/20 20:56:05 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		env_cell_delete(void	*ptr)
{
	t_env_cell	*cell;

	cell = (t_env_cell *)ptr;
	ft_strdel(&cell->key);
	ft_strdel(&cell->value);
}

int		env_unset(t_env *env, char *key)
{
	fta_popindexf(&env->tab, ARRAY_IFP(&env->tab,
				find_cell(env, key)), 1, env_cell_delete);
	return (0);
}
