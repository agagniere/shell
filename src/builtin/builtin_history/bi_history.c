/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:45:49 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/27 17:24:19 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	history_str(const void *ptr)
{
	const char *str = ptr;

	ft_putendl(str);
}

void		bi_history_print(t_history *history)
{
		fta_iter(&history->tab, &history_str);
}

int		bi_history_save(t_history *history, char *cmd)
{
	
	int			fd;

	fd = open("/tmp/42sh_history.txt", O_RDWR | O_APPEND);
	fta_append(&history->tab, cmd, 1);
	ft_putendl_fd(cmd, fd);
	close(fd);
	history->index = history->tab.size;
	return (0);
}

int		bi_history_init(t_history *history)
{
	int			fd;
	int			ret;
	char		*str;

	history->tab = NEW_ARRAY(char *);
	history->tmp_cmd = NEW_STRING;
	if (fta_reserve(&history->tab, 1000))
		return (1);
	if ((fd = open("/tmp/42sh_history.txt", O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		fd = open("/tmp/42sh_history.txt", O_RDWR);
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		fta_append(&history->tab, str, 1);
		free(str);
	}
	close(fd);

	return (0);
}

int		bi_change_str(t_line *line, t_history *history)
{
	t_string	tmp;

	tmp = NEW_STRING;
	tmp.data = *ARRAY_GETT(char *, &history->tab, history->index);
	tmp.size = ft_strlen((char *)tmp.data);
	tmp.max = tmp.size;
	line->cursor = 0;
	fta_overwrite(&history->tmp_cmd, &line->str);
	fta_overwrite(&line->str, &tmp);
	line->sauv_cursor = tmp.size;
	print(line);
	return (0);
}
