/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:29:03 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/24 21:21:11 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomp.h"

static t_actions const g_actions[1] = {
	{NULL, {9, 0, 0, 0, 0, 0}, "TAB"},
};

static void		replace_auto(t_line *line, t_autocomp *autocomp)
{
	t_string	*tmp;
	size_t		end;
	size_t		start;
	size_t		len;

	start = get_start_erase(line);
	end = get_end_erase(line);
	if (end >= start)
		len = end - start;
	else
		len = 0;
	if (autocomp->first_time == 1)
		line->cursor = line->cursor - len;
	tmp = ARRAY_GETT(t_string, &autocomp->tab_a, autocomp->index);
	fta_replace(&line->str, start, len, tmp);
	autocomp->cursor_tmp = tmp->size;
}

static void		do_autocomp(t_line *line, t_autocomp *autocomp)
{
	while (1)
	{
		my_read(line, &autocomp->first_time);
		if (cmp_buf((int *)g_actions[0].value, line->buffer) == 0)
		{
			if (autocomp->tab_a.size > 0)
			{
				if (autocomp->index == autocomp->tab_a.size)
					autocomp->index = 0;
				replace_auto(line, autocomp);
				line->sauv_cursor = line->cursor + autocomp->cursor_tmp;
				ft_home(line);
				print(line);
				print_auto(line, autocomp);
				autocomp->index++;
			}
		}
		else
		{
			actions(line);
			break ;
		}
	}
}

int				create_tab_a(t_autocomp *autocomp)
{
	t_aut_info		info;
	t_string		tmp;

	tmp = NEW_STRING;
	if ((info.dirp = opendir((char *)autocomp->path.data)) != NULL)
	{
		while ((info.dp = readdir(info.dirp)) != NULL)
		{
			if (!(info.dp->d_name[0] == '.'
						&& ((char*)autocomp->str.data)[0] == '\0'))
				if (ft_strncmp(info.dp->d_name, ".", 1) != 0
						&& ft_strncmp(info.dp->d_name, "..", 2) != 0
						&& ft_strncmp(info.dp->d_name,
						(char *)autocomp->str.data, autocomp->str.size) == 0)
				{
					STR_JOIN_CS(&tmp, info.dp->d_name,
							ft_strlen(info.dp->d_name));
					STR_NULL_TERMINATE(&tmp);
					fta_append(&autocomp->tab_a, &tmp, 1);
					tmp = NEW_STRING;
				}
		}
		closedir(info.dirp);
	}
	return (0);
}

static void		autocomp_init(t_line *line, t_autocomp *autocomp)
{
	autocomp->tab_a = NEW_ARRAY(t_string);
	autocomp->line_tmp = fta_new(sizeof(char));
	fta_overwrite(&autocomp->line_tmp, &line->str);
	STR_NULL_TERMINATE(&autocomp->line_tmp);
	autocomp->path = fta_new(sizeof(char));
	autocomp->str = fta_new(sizeof(char));
	autocomp->first_time = 0;
	autocomp->index = 0;
	autocomp->nl = 0;
	autocomp->cursor_tmp = 0;
}

void			ft_autocomp(t_line *line)
{
	t_autocomp	autocomp;

	autocomp_init(line, &autocomp);
	init_str(&autocomp, line);
	if (verif_if_fnc(line->cursor, (char *)line->str.data) == 1)
		cmd_fnc(&autocomp);
	else
		create_tab_a(&autocomp);
	do_autocomp(line, &autocomp);
}
