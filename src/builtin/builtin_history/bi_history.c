/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:45:49 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/17 19:24:14 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		bi_history_save(t_array *history, char *cmd)
{
	
	int			fd;

	fd = open("/tmp/42sh_history.42sh", O_APPEND);
	fta_append(history, str, 1);
	ft_putendl_fd(str, fd);
	close(fd);
}

int		bi_history_init(t_array *history)
{
	int			fd;
	int			ret;
	char			*str;

	fd = open("/tmp/42sh_history.42sh", O_RDWR | O_CREAT);
	while ((ret = get_next_line(fd, &str)))
	{
		fta_append(history, &str, 1);
		free(str);
	}
	close(fd);
	return (0)
}
