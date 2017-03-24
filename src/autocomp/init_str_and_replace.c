/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_str_and_replace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 21:15:22 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/24 21:20:21 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomp.h"

int				cmd_fnc(t_autocomp *autocomp)
{
	char		**tab_path;
	t_env_cell	*cell;
	size_t		i;
	t_string	tmp;

	i = 0;
	tmp = NEW_STRING;
	cell = find_cell(&g_env, "PATH");
	if (cell == NULL)
		return (1);
	tab_path = ft_strsplit(cell->value, ':');
	while (tab_path[i] != NULL)
	{
		STR_JOIN_CS(&tmp, tab_path[i], ft_strlen(tab_path[i]));
		fta_overwrite(&autocomp->path, &tmp);
		STR_NULL_TERMINATE(&autocomp->path);
		create_tab_a(autocomp);
		tmp = NEW_STRING;
		i++;
	}
	return (0);
}

int				verif_if_fnc(size_t i, char *str)
{
	if (str[i] == '/' || str[i] == '.')
		return (0);
	if (i == 0)
		return (1);
	else
	{
		while (i > 0 && str[i - 1] != ' ')
			i--;
		while (i > 0 && str[i - 1] == ' ')
			i--;
		if (i == 0)
			return (1);
		else if (str[i - 1] == '|' || str[i - 1] == ';')
			return (1);
	}
	return (0);
}

void			join_cs(t_autocomp *autocomp, char *ptr, char *ptr2)
{
	if (ptr2 == NULL)
	{
		STR_JOIN_CS(&autocomp->str, ptr, ft_strlen(ptr));
		STR_JOIN_CS(&autocomp->path, ".", 1);
	}
	else
	{
		*ptr2 = '\0';
		ptr2++;
		if (*ptr == ' ')
			STR_JOIN_CS(&autocomp->path, ".", 1);
		else if (ptr2 - 1 == ptr)
			STR_JOIN_CS(&autocomp->path, "/", 1);
		else
			STR_JOIN_CS(&autocomp->path, ptr, ft_strlen(ptr));
		STR_JOIN_CS(&autocomp->str, ptr2, ft_strlen(ptr2));
	}
}

void			init_str(t_autocomp *autocomp, t_line *line)
{
	char		*ptr;
	char		*ptr2;
	size_t		i;

	i = line->cursor;
	ptr = (char *)autocomp->line_tmp.data;
	ptr2 = (char *)autocomp->line_tmp.data;
	while (i > 0 && ptr[i - 1] != ' ')
		i--;
	ptr += i;
	i = line->cursor;
	while (i < autocomp->line_tmp.size && ptr2[i] != ' ' && ptr2[i] != '/')
		i++;
	if (ptr2[i] == ' ' || ptr2[i] == '/')
		ptr2[i] = '\0';
	ptr2 = ft_strrchr(ptr, '/');
	join_cs(autocomp, ptr, ptr2);
	STR_NULL_TERMINATE(&autocomp->path);
	STR_NULL_TERMINATE(&autocomp->str);
}
