/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 16:54:21 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/06 18:11:09 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
t_env			g_env;

int				env_print(t_env	*env)
{
	t_env_cell	const ** tab = env->tab.data;
	size_t		i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		printf("%s=%s\n",tab[i]->key, tab[i]->value);
		i++;
	}
	return (0);
}

int				main(int ac, char **av, char **environ)
{
	t_env			env;
	int				ex;

	ex = 0;
	ac = 0;
	(void)av;
	env_init(&g_env, environ);
	env_print(&g_env);
	return (ex);
}
