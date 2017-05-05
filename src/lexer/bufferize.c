/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 21:29:23 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/05 23:25:13 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		bufferize(t_tokenizer *self)
{
	t_string	total[1];
	uint8_t		quote;

	*total = NEW_STRING;
	quote = (IS_CURRENTC(self->in) == '\'') && ++(self->in->buff_i);
	self->current.tag = quote ? SH_TEXT : SH_WORD;
	while (1/* ... */)
	{
		self->current.data.str = IS_CURRENT(self->in);
		while (self->in->buff_i < self->in->buff_len
			&& !(quote ? IS_CURRENTC(self->in) == '\''
			: ft_strchr(" \t&()|{};<>", IS_CURRENTC(self->in))))
			self->in->buff_i++;
	}
}
