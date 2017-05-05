/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:25:42 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/05 23:12:22 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

#include <stdio.h> // <--

int
	bslash(t_tokenizer *self)
{
	self->in->buff_i++;
	if (IS_REFRESH(self->in))
		return (self->eof = 3);
	self->current.tag = SH_BSLASH;
	self->current.data.len = 1;
	self->current.data.str = (char *)IS_CURRENT(self->in);
	return (0);
}

static int
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
		bool = IS_BLANK(IS_CURRENTC(self->in));
	}
	return (0);
}

int
	sh_tokenize(t_tokenizer *self)
{
	int				i;
	void *const		f[] = {&bslash, &map0, &map1, &map2, &map3};

	printf("sh_tokenize\n");
	self->current.data.len = 0;
	if (self->eof)
		return (1);
	else if (IS_REFRESH(self->in) || IS_CURRENTC(self->in) == '\0')
		return (self->eof = 1);
	else if (0 <= (i = is_in(IS_CURRENTC(self->in), "\";`$(){}")))
		one_char(self, i);
	else if (0 <= (i = is_in(IS_CURRENTC(self->in), "\\><|&")))
	{
		self->in->buff_i++;
		return (((int (*)())(f + i))(self));
	}
	else if (IS_BLANK(IS_CURRENTC(self->in)))
		return (gap(self));
	else
		return (bufferize(self));
	return (0);
}

/************************************************/

static int
	word(t_tokenizer *self)
{
	uint8_t	bool;

	printf("word\n");
	self->current.tag = SH_WORD;
	self->current.data.str = (char *)IS_CURRENT(self->in);
	bool = 0;
	int tmp = 1;
	while (!bool)
	{
		self->in->buff_i++;
		if (self->in->buff_i >= self->in->buff_len)
			break ;
		if (ft_strchr("\"'\\`$", IS_CURRENTC(self->in)))
			bool = (self->current.tag = SH_TEXT);
		bool = bool
			|| ft_strchr("&()|{};<>", IS_CURRENTC(self->in))
			|| IS_CURRENTC(self->in) == '\0';
		printf("Loop %i : '%c' %i %i, \n", tmp++,
			   IS_CURRENTC(self->in), IS_BLANK(IS_CURRENTC(self->in))), bool;
	}
	self->current.data.len = IS_CURRENT(self->in) - self->current.data.str;
	return (0);
}
