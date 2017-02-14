/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:13:22 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/14 17:20:31 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*env_cell_to_char(t_env_cell *cell)
{
	char	*str;

	str = ft_strnew(ft_strlen(cell->key) + ft_strlen(cell->value) + 1);
	ft_strcpy(str, cell->key);
	ft_strcpy(str, "=");
	ft_strcpy(str, cell->value);
	return (str);
}

void	env_char_delete(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_strdel(&env[i]);
		i++;
	}
	free(env);
	env = NULL;
}

char	**env_char_create(t_env	*env)
{
	char				**ret;
	t_env_cell	**const tab = env->tab.data;
	size_t				i;

	i = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * (env->tab.size + 1))))
		return (NULL);
	while (i < env->tab.size)
	{
		ret[i] = env_cell_to_char(tab[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
