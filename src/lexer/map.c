/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:41:50 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/10 12:32:44 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

/*
** >
** Right
*/
int		map0(t_tokenizer *self)
{
	const uint8_t	t[] = {SH_DRIGHT, SH_CLOBBER, SH_RIGHTAND};
	int				i;

	self->current.tag = SH_RIGHT;
	if (IS_REFRESH(self->in))
		return (self->eof = 1);
	if ((i = is_in(IS_CURRENTC(self->in), ">|&")))
	{
		self->in->buff_i++;
		self->current.tag = t[i];
	}
	return (0);
}

/*
** <
** Left
*/
int		map1(t_tokenizer *self)
{
	const uint8_t	t[] = {SH_DLEFT, SH_RW, SH_LEFTAND};
	int				i;

	self->current.tag = SH_LEFT;
	if (IS_REFRESH(self->in))
		return (self->eof = 1);
	if ((i = is_in(IS_CURRENTC(self->in), "<>&")))
	{
		self->in->buff_i++;
		self->current.tag = t[i];
		if (IS_REFRESH(self->in))
			return (self->eof = 1);
		if ((IS_CURRENTC(self->in) == '-' && (self->current.tag = SH_DLEFTD))
			|| (IS_CURRENTC(self->in) == '<' && (self->current.tag = SH_TLEFT)))
			self->in->buff_i++;
	}
	return (0);
}


/*
** |
** Pipe
*/
int		map2(t_tokenizer *self)
{
	self->current.tag = SH_PIPE;
	if (IS_REFRESH(self->in))
		return (self->eof = 1);
	if ((IS_CURRENTC(self->in) == '|' && (self->current.tag = SH_OR))
		|| (IS_CURRENTC(self->in) == '&' && (self->current.tag = SH_PIPEAND)))
		self->in->buff_i++;
	return (0);
}


/*
** &
** Ampersand
*/
int		map3(t_tokenizer *self)
{
	self->current.tag = SH_AMPER;
	if (IS_REFRESH(self->in))
		return (self->eof = 1);
	if ((IS_CURRENTC(self->in) == '&' && (self->current.tag = SH_AND))
		|| (IS_CURRENTC(self->in) == '>' && (self->current.tag = SH_ANDRIGHT)))
		self->in->buff_i++;
	return (0);
}
