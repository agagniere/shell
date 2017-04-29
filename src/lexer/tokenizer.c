/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:25:42 by angagnie          #+#    #+#             */
/*   Updated: 2017/04/30 01:07:18 by sid              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

int
	bslash(t_tokenizer *self)
{
	self->in->buff_i++;
	if (IS_REFRESH(self->in))
		return (self->eof = 3);
	self->current.tag = SH_BSLASH;
	self->current.data.len = 1;
	return (0);
}

int
	quote(t_tokenizer *self)
{
	int	bool;

	self->current.tag = SH_TEXT;
	bool = 1;
	while (bool)
	{
		self->in->buff_i++;
		if (IS_REFRESH(self->in))
			return (self->eof = 2);
		bool = IS_CURRENTC(self->in) != '\'';
	}
	self->current.data.len = IS_CURRENT(self->in) - self->current.data.str;
	return (0);
}

static int
	word(t_tokenizer *self)
{
	int	bool;

	self->current.tag = SH_WORD;
	self->current.data.str = (char *)IS_CURRENT(self->in);
	bool = 1;
	while (bool)
	{
		self->in->buff_i++;
		if (IS_REFRESH(self->in))
			return (self->eof = 1);
		if (ft_strchr("\"'\\!", IS_CURRENT))
			bool = (self->current.tag = SH_TEXT);
		bool = bool || ISBLANK(IS_CURRENTC(self->in));
	}
	return (0);
}

static int
	one_char(t_tokenizer *self, int i)
{
	uint8_t	*const tag = {SH_DQUOTE, SH_SEMI, SH_BQUOTE, SH_DOLLAR};

	self->in->buff_i++;
	self->current.tag = tag[i];
	return (0);
}

int
	sh_tokenize(t_tokenizer *self)
{
	int		i;
	void	*const f = {&quote, &bslash, &map0, &map1, &map2, &map3};

	self->current.data.len = 0;
	if (self->eof)
		return (1);
	else if (IS_REFRESH(self->in))
		return (self->eof = 1);
	else if (0 <= (i = is_in(IS_CURRENTC(self->in), "\";`$")))
		one_char(self, i);
	else if (0 <= (i = is_in(IS_CURRENTC(self->in), "'\\><|&")))
		return (((int (*)())(f + i))(self));
	else
		return (word(self));
	return (0);
}
