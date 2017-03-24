/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_erase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 21:11:18 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/24 21:15:02 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomp.h"

void		my_read(t_line *l, int *first_time)
{
	ft_bzero(l->buffer, 6);
	if (*first_time == 0 && (*first_time = 1))
		l->buffer[0] = 9;
	else
		read(STDIN_FILENO, l->buffer, 6);
}

int			cmp_buf(int *value, char *buf)
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

size_t		get_end_erase(t_line *line)
{
	size_t	i;
	char	*ptr;

	ptr = line->str.data;
	i = line->cursor;
	while (i < line->str.size && ptr[i] != '/' && ptr[i] != ' ')
		i++;
	return (i);
}

size_t		get_start_erase(t_line *line)
{
	size_t	i;
	char	*ptr;

	ptr = line->str.data;
	i = line->cursor;
	while (i > 0 && ptr[i - 1] != '/' && ptr[i - 1] != ' ')
		i--;
	return (i);
}
