/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:45:49 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/23 18:33:23 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	history_str(const void *ptr)
{
	const char *str = ptr;

	ft_putendl(str);
}

void		bi_history_print(t_array *history)
{
		fta_iter(history, &history_str);
}

int		bi_history_save(t_array *history, char *cmd)
{
	
	int			fd;

	fd = open("/tmp/42sh_history.txt", O_RDWR | O_APPEND);
	fta_append(history, cmd, 1);
	ft_putendl_fd(cmd, fd);
	close(fd);
	return (0);
}

int		bi_history_init(t_array *history)
{
	int			fd;
	int			ret;
	char		*str;

	*history = NEW_ARRAY(char *);
	if (fta_reserve(history, 10))
		return (1);
	if ((fd = open("/tmp/42sh_history.txt", O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		fd = open("/tmp/42sh_history.txt", O_RDWR);
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		fta_append(history, str, 1);
		free(str);
	}
	close(fd);

	return (0);
}
