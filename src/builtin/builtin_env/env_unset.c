/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:53:22 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/20 16:16:59 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		env_cell_delete(void	*ptr)
{
	t_env_cell	*cell;

	cell = (t_env_cell *)ptr;
	ft_strdell(&cell->key);
	ft_strdell(&cell->value);
}

int		env_unset(t_env *env, t_env_cell *cell)
{
	return (0);
}
