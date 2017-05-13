/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 10:53:27 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/13 13:27:13 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Inside a "
*/

static int		dqbs(t_tokenizer *self)
{
	self->in->buff_i++;
	if (IS_REFRESH(self->in))
		return (self->eof = 3);
	else if (IS_CURRENTC(self->in) == '\n')
		return (self->current.data.len = 0);
	else if (ft_strchr("\"$\\!", IS_CURRENTC(self->in)))
	{
		self->current.data.str = IS_CURRENT(self->in);
		self->current.data.len = 1;
	}
	else
		self->current.data.len = 2;
	return (0);
}

int				tk_dquote(t_tokenizer *self)
{
	self->current.tag = SH_TEXT;
	self->current.data.str = IS_CURRENT(self->in);
	if (IS_CURRENTC(self->in) == '\\')
		return (dqbs(self));
	while (self->in->buff_i < self->in->buff_len
		&& !ft_strchr("\"`$\\", IS_CURRENTC(self->in)))
		self->in->buff_i++;
	self->current.data.len = IS_CURRENT(self->in) - self->current.data.len;
	return (0);
}

/*
**
*/

static int		adhoc_atoi(t_string str, char **ptr)
{
	int			n;
	uint8_t		sign;

	n = 0;
	sign = (*ptr == '-' && (*ptr)++ ? -1 : 1);
	if (**ptr == '!')
		return (-1);
	while (IS_DIGIT(**ptr))
	{
		n = 10 * n + (**ptr - '0') * sign;
		(*ptr)++;
	}
	return (ans);
}

/*
** Lookin 4 da !
** -
** This doesnt support subshells.
*/

int		spot_exclamation(t_string *str)
{
	uint8_t		on;
	uint8_t		quote_on;
	char		*current = STR_GET(str, -1);

	on = 1;
	quote_on = 1;
	while (++current < ARRAY_END(str))
	{
		if (on && *current == '!' && ++current)
			adhoc_atoi(str, &current);
		else if (*current == '\\')
			current++;
		else if (quote_on && *current == '\'')
			on = !on;
		else if (on && *current == '"')
			quote_on = !quote_on;
	}
}
