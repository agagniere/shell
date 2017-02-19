/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:13:22 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/19 16:47:18 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_string.h"

char	*env_cell_to_char(t_env_cell *cell)
{
	char	*str;
	size_t	len[2];

	len[0] = ft_strlen(cell->key);
	len[1] = ft_strlen(cell->value);
	if (!(str = ft_strnew(len[0] + len[1] + 1)))
		return (NULL);
	ft_strcpy(str, cell->key);
	ft_strcpy(str + len[0], "=");
	ft_strcpy(str + len[0] + 1, cell->value);
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

/*
** Cool enough
*/

t_string	env_cell_to_string(t_env_cell *cell)
{
	t_string		ans;
	const t_substr	key = NEW_SUB(cell->key);
	const t_substr	val = NEW_SUB(cell->value);

	ans = NEW_STRING;
	STR_JOIN(&ans, &key);
	STR_JOIN_CS(&ans, "=", 1);
	STR_JOIN(&ans, &val);
	return (ans);
}

/*
** Environement To Array<String>
** -
** How vectors enable us to forget about malloc,
** ft_strnew and such. Plus, iterators are cool !
** -
** returns an array of strings containing each environement entry
** converted to string.
*/

t_array		alternate_env2str(t_env *env)
{
	t_array		ans;
	t_string	entry;
	void		*ite;
	t_env_cell	*cell;

	ans = NEW_ARRAY(t_string);
	ite = ARRAY_ITERATOR(&env->tab);
	while (ARRAY_HASNEXT(&env->tab, ite))
	{
		cell = (t_env_cell *)ite;
		entry = env_cell_to_string(cell);
		fta_append(&ans, &entry, 1);
	}
	return (ans);
}
