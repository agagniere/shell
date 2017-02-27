/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:45:49 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/27 19:20:58 by malaine          ###   ########.fr       */
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
		fta_iter(&history->tab_h, &history_str);
}

int		bi_history_save(t_history *history, char *cmd)
{
	
	int			fd;

	fd = open("/tmp/42sh_history.txt", O_RDWR | O_APPEND);
	fta_append(&history->tab_h, cmd, 1);
	ft_putendl_fd(cmd, fd);
	close(fd);
	history->index = history->tab_h.size - 1;
	return (0);
}

int		bi_history_init(t_history *history)
{
	int			fd;
	int			ret;
	char		*str;

	history->tab_h = NEW_ARRAY(t_string);
	history->tmp_cmd = NEW_STRING;
	if (fta_reserve(&history->tab_h, 1000))
		return (1);
	if ((fd = open("/tmp/42sh_history.txt", O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		fd = open("/tmp/42sh_history.txt", O_RDWR);
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		STR_JOIN_CS(&history->tmp_cmd, (void *)str, ft_strlen(str));
		fta_append(&history->tab_h, &history->tmp_cmd, 1);
		history->tmp_cmd = NEW_STRING;
		free(str);
	}
	close(fd);
	history->index = history->tab_h.size - 1;
	return (0);
}

char *identity(void *ptr)
{
	return ((char *)(((t_string *)ptr)->data));
}

int		bi_change_str(t_line *line, t_history *history)
{
	t_string	tmp;

	tmp = *ARRAY_GETT(t_string, &history->tab_h, history->index);
	line->sauv_cursor = tmp.size;
	ft_home(line);
	do_term("cd");
	fta_overwrite(&history->tmp_cmd, &line->str);
	fta_overwrite(&line->str, &tmp);
	print(line);
	return (0);
}
