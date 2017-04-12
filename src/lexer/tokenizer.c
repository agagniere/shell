/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:25:42 by angagnie          #+#    #+#             */
/*   Updated: 2017/04/12 16:10:20 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "ft_stream.h"

int		sh_tokenize(t_tokenizer *self)
{
	char c;

	if (self->in->buff_i >= self->in->buff_len)
		IS_REFESH(self->in);
	c = IS_CURRENTC(self->in);
	// ...
	return (0);
}
