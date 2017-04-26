/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:25:42 by angagnie          #+#    #+#             */
/*   Updated: 2017/04/26 19:31:32 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

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
	self->current.data.len = IS_CURRENT(self->in) - self->current.data.str;
	return (0);
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
			return (self->eof = 1);
		bool = ft_strchr("\";><|&!$`\\", IS_CURRENTC(self->in));
	}
	return (0);
}

int
	sh_tokenize(t_tokenizer *self)
{
	int		i;
	void	*const t = {map0, map1, map2, map3, map4, map5, map6, map7, map8};

	if (self->eof)
		return (1);
	if (IS_REFRESH(self->in))
		return ((self->eof = 1));
	self->current.tag = SH_WORD;
	self->current.data.str = (char *)IS_CURRENT(self->in);
	if (IS_CURRENTC(self->in) == '\'')
		return (quote(self));
	else if (IS_CURRENTC(self->in) == '\\')
		return (bslash(self));
	else if (0 <= (i = is_in(IS_CURRENTC(self->in), "\";><|&!$`")))
	{
		self->current.data.len = 0;
		self->in->buff_i++;
		return (((int (*)())(t + i))(self));
	}
	else
		return (word(self));
	return (1);
}
