/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 21:29:23 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/19 16:06:42 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		bufferize(t_tokenizer *self)
{
	t_string	total[1];
	uint8_t		quote;
	uint8_t		bool;

	*total = NEW_STRING;
	quote = (IS_CURRENTC(self->in) == '\'') && ++(self->in->buff_i);
	self->current.tag = quote ? SH_TEXT : SH_WORD;
	bool = 1;
	while (bool)
	{
		if (IS_REFRESH(self->in))
			break;
		self->current.data.str = (char *)IS_CURRENT(self->in);
		while (self->in->buff_i < self->in->buff_len
			&& !(quote ? (int)IS_CURRENTC(self->in) == '\''
				 : (int)ft_strchr(" ;|<>'\"`(){}&\t", IS_CURRENTC(self->in))))
			self->in->buff_i++;
		self->current.data.len = IS_CURRENT(self->in) - self->current.data.str;
		STR_JOIN(total, &self->current.data);
		bool = self->in->buff_i >= self->in->buff_len;
	}
	fta_trim(total);
	self->current.data.str = total->data;
	self->current.data.len = total->size;
	if (quote && bool)
		return (self->eof = 2);
	else if (quote)
		self->in->buff_i++;
	if (!quote && ft_strchr("'\"`\\", IS_CURRENTC(self->in)))
		self->current.tag = SH_TEXT;
	return (0);
}
