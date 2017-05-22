/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:25:42 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/22 13:38:20 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

int
	bslash(t_tokenizer *self)
{
	if (IS_REFRESH(self->in))
		return (self->eof = 3);
	self->current.tag = SH_BSLASH;
	self->current.data.len = 1;
	self->current.data.str = (char *)IS_CURRENT(self->in);
	self->in->buff_i++;
	return (0);
}

int
	one_char(t_tokenizer *self, int i)
{
	const uint8_t	tag[] = {SH_DQUOTE, SH_SEMI, SH_BQUOTE, SH_DOLLAR,
							 SH_OPAR, SH_CPAR, SH_OBRACE, SH_CBRACE};

	self->in->buff_i++;
	self->current.tag = tag[i];
	return (0);
}

static int
	gap(t_tokenizer *self)
{
	uint8_t		bool;

	self->current.tag = SH_GAP;
	bool = 1;
	while (bool)
	{
		self->in->buff_i++;
		if (IS_REFRESH(self->in))
			return (self->eof = 1);
		bool = IS_BLANK(IS_CURRENTC(self->in))
			|| IS_CURRENTC(self->in) == '\n';
	}
	return (0);
}

int
	sh_tokenize(t_tokenizer *self)
{
	int				i;
	int (*const		f[])()	= {&bslash, &map0, &map1, &map2, &map3};

	self->current.data.len = 0;
	if (self->eof)
		return (1);
	else if (IS_REFRESH(self->in) || IS_CURRENTC(self->in) == '\0')
		return (self->eof = 1);
	else if (IS_CURRENTC(self->in) == '\n')
		one_char(self, 1);
	else if (0 <= (i = is_in(IS_CURRENTC(self->in), "\";`$(){}")))
		one_char(self, i);
	else if (0 <= (i = is_in(IS_CURRENTC(self->in), "\\><|&")))
	{
		self->in->buff_i++;
		return ((f[i])(self));
	}
	else if (IS_BLANK(IS_CURRENTC(self->in)))
		return (gap(self));
	else
		return (bufferize(self));
	return (0);
}
