/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:40:08 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/17 15:29:56 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_cell		*find_cell(t_env *env, char *key)
{
	void		*iterator;
	t_env_cell	*cell;

	iterator = ARRAY_ITERATOR(&env->tab);
	while (ARRAY_HASNEXT(&env->tab, iterator))
	{
		cell = (t_env_cell *)iterator;
		if (ft_strcmp(key, cell->key))
			return (cell);
	}
	return (NULL);
}

t_env_cell	*env_new_cell(char *key, char *value)
{
	t_env_cell	*cell;

	if (!(cell = (t_env_cell *)malloc(sizeof(t_env_cell))))
		return (NULL);
	cell->key = ft_strdup(key);
	cell->value = ft_strdup(value);
	return (cell);
}

int		env_cell_modif(t_env_cell *cell, char *value)
{
	ft_strdel(&cell->value);
	cell->value = ft_strdup(value);
	return (0);
}

int		env_set(t_env *env, char *key, char *value)
{
	t_env_cell	*cell;

	cell = find_cell(env, key);
	if (cell == NULL)
	{
		cell = env_new_cell(key, value);
		fta_append(&env->tab, &cell, 1);
	}
	else
		env_cell_modif(cell, value);
	return (0);
}
