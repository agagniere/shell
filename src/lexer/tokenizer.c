/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:25:42 by angagnie          #+#    #+#             */
/*   Updated: 2017/04/20 20:03:31 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "ft_stream.h"

static int
	bslash(t_tokenizer *self)
{
	self->in->buff_i++;
	if (IS_REFRESH(self->in))
		return (self->eof = 3);
	self->current.tag = SH_BSLASH;
	self->current.data.len = 1;
	return (0);
}

static int
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
	self->current.
	return (0);
}

static int
	map(t_tokenizer *self)
{
}

static int
	word(t_tokenizer *self)
{
	int	bool;

	bool = 1;
	while (bool)
	{
		self->in->buff_i++;
		if (IS_REFRESH(self->in))
			return (self->eof = 2);
		bool = is_in(IS_CURRENTC(self->in), '\'');
	}
	return (0);
}

int
	sh_tokenize(t_tokenizer *self)
{
	if (self->eof)
		return (1);
	if (IS_REFESH(self->in))
		return (1);
	self->current.tag = SH_WORD;
	self->current.data.str = IS_CURRENT(self->in);
	if (IS_CURRENTC(self->in) == '\'')
		return (quote(self));
	else if (IS_CURRENT(self->in) == '\\')
		return (bslash(self));
	else if (self->map && 0  is_in(IS_CURRENTC(self->in), "\";><|&!$"))
		return (map(self));
	else
		return (word(self));
	return (1);
}
