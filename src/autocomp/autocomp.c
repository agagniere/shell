/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:29:03 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/03 21:03:26 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_actions const g_actions[1] = {
	{NULL, {9, 0, 0, 0, 0, 0}, "TAB"},
};

static void			my_read(t_line *l, int *first_time)
{
	ft_bzero(l->buffer, 6);
	if (*first_time == 0 && (*first_time = 1))
		l->buffer[0] = 9;
	else
		read(STDIN_FILENO, l->buffer, 6);
}

static int			cmp_buf(int *value, char *buf)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (buf[i] != value[i])
			return (1);
		i++;
	}
	return (0);
}

static void		do_autocomp(t_line *line, t_autocomp *autocomp)
{
	while (1)
	{
		my_read(l, first_time);
		if (cmp_buf((int *)g_actions[0].value, l->buffer) == 0)
		{
			if (autocomp->index == autocomp->tab_a.size)
				autocomp->index = 0;
				
			autocomp->index++;
		}
		else
		{
			actions(l);
			break ;
		}
	}
}

int				tmp_cmp()
{

}

int				create_tab_a(t_autocomp *autocomp)
{
	t_aut_info		info;
	t_string		tmp;

	tmp = NEW_STRING;
	if ((info.dirp = opendir(autocomp->path)) != NULL)
	{
		while ((info.dp = readdir(info.dp)) != NULL)
		{
			if (!(info.dp->d_name[0] == '.' && str[0] == '\0'))
				if (ft_strncmp(info.dp->d_name, ".", 1) != 0
						&& ft_strncmp(info.dp->d_name, "..", 2) != 0
						&& ft_strncmp(info.dp->d_name,
							(char *)autocomp->str.data, autocomp->str.size) == 0)
				{
					STR_JOIN_CS(&tmp, (void *)info.dp->d_name,
							ft_strlen(info.dp->d_name));
					fta_append(&autocomp->tab_a, tmp, 1);
					tmp.size = 0;
				}
		}
		closedir(info.dirp);
	}
}

static void		autocomp_init(t_autocomp *autocomp)
{
	autocomp->tab_a = NEW_ARRAY(t_string);
	autocomp->path = NEW_STRING;
	autocomp->str = NEW_STRING;
	autocomp->first_time = 0;
	autocomp->index = 0;
}

void			ft_autocomp(t_line *line)
{
	t_autocomp	autocomp;

	autocomp_init(&autocomp);
	create_tab_a(&autocomp);
	do_autocomp();
}
