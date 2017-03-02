/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:45:49 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/02 19:12:29 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "edit_line.h"

static void	history_str(const void *ptr)
{
	const char *str = ptr;

	ft_putendl(str);
}

void		bi_history_print(t_history *history)
{
		fta_iter(&history->tab_h, &history_str);
}

int		bi_history_save(t_history *history, t_string *cmd)
{
	
	int			fd;

	fta_reserve(&history->tab_h, 2);
	fd = open("/tmp/42sh_history.txt", O_RDWR | O_APPEND);
	fta_append(&history->tab_h, cmd, 1);
	FTSZ(cmd);
	ft_putendl_fd((char *)cmd->data, fd);
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

char *sp_putchar(void *c)
{
	char ans[2];

	ans[0] = *(char *)c;
	ans[1] = 0;
	return (ft_strdup(ans));
}

size_t		search_history(t_line *l, t_history *history, bool up_or_down)
{
	size_t i;

		
	i = history->index + (up_or_down ? -1 : 1);
	if (l->cursor == 0)
		return (i);
	while (ARRAY_INDEX_CHECK(&history->tab_h, i) &&
		   ft_strncmp(ARRAY_GETT(t_string, &history->tab_h, i)->data,
		   l->str.data, l->cursor) != 0)
		i += up_or_down ? -1 : 1;
	if (ARRAY_INDEX_CHECK(&history->tab_h, i))
	{
		printf("  %s\n", fta_string(ARRAY_GETT(t_string,
			&history->tab_h, i), sp_putchar));
		return (i);
	}
	return (history->index);
}


int		bi_change_str(t_line *line, t_history *history, size_t new)
{
	t_string	*tmp;

	if (new != history->index)
	{
		tmp = ARRAY_GETT(t_string, &history->tab_h, history->index);
		fta_overwrite(tmp, &line->str);
		tmp = ARRAY_GETT(t_string, &history->tab_h, new);
		fta_overwrite(&line->str, tmp);
		history->index = new;
		line->sauv_cursor = line->cursor;
		ft_home(line);
		do_term("cd");
		print(line);
	}
	return (0);
}
