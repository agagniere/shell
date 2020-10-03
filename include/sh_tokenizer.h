/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:50:15 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/23 14:27:13 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENIZER_H
# define SH_TOKENIZER_H

# include "ft_token.h"

# include <stdio.h> // <====

typedef enum e_sh_token		t_sh_token;

enum						e_sh_token
{
	SH_NONE, //				0000 0000

	SH_SEMI = 2, //	;	1	0000 0010
	SH_AMPER, //	&		0000 0011

	SH_AND, //		&&	2	0000 0100
	SH_OR, //		||		0000 0101

	SH_PIPE = 0x08,//|	3	0000 1000

	SH_RIGHT = 0x10,//>	4	0001 0000
	SH_CLOBBER, //	>|		0001 0001
	SH_DRIGHT, //	>>		0001 0010
	SH_LEFT, //		<		0001 0011
	SH_DLEFT, //	<<		0001 0100
	SH_DLEFTD, //	<<-		0001 0101
	SH_TLEFT, //	<<<		0001 0110
	SH_LR, //		<>		0001 0111
	SH_RIGHTAND, // >&		0001 1000
	SH_LEFTAND, //	<&		0001 1001

	SH_PIPEAND, //	|&		0001 1010
	SH_ANDRIGHT, //	&>		0001 1011

	SH_WORD = 0x80, //		1000 0000
	SH_TEXT, //				1000 0001
	SH_BSLASH, //	\		1000 0010

	SH_LIST = 0xa0, //		1010 0000
	SH_CAT, //				1010 0001
	SH_SUBSHELL, //			1010 0010

	SH_OPAR = 0xe0,//(		1110 0011
	SH_CPAR, //		)		1110 0100
	SH_OBRACE, //	{		1110 0101
	SH_CBRACE, //	}		1110 0110
	SH_DOLLAR, //	$		1110 0111
	SH_DQUOTE, //	"		1110 1000
	SH_BQUOTE, //	`		1110 1001
	SH_GAP, //				1110 1010

	SH_SEMICOLON = SH_SEMI,
	SH_AMPERSAND = SH_AMPER,
	SH_APPEND = SH_DRIGHT,
	SH_HEREDOC = SH_DLEFT,
	SH_HEREDOCT = SH_DLEFTD,
	SH_HERESTR = SH_TLEFT,
	SH_RW = SH_LR
};

/*
** |	----------===== public: =====----------
*/

int							sh_tokenize(t_tokenizer *self);
int							tk_dquote(t_tokenizer *self);
int							bufferize(t_tokenizer *self);

# define SH_IS_SEPARATOR(T) _2BIT(T)
# define SH_IS_LOGICAL(T) (_3BIT(T) && !_2BIT(T))
# define SH_IS_REDIRECTION(T) (_5BIT(T) && !_4BIT(T))
# define SH_IS_FLEAF(T) (_8BIT(T) && !_XTND(T))
# define SH_IS_XLEAF(T) (_8BIT(T) && _XTND(T))
# define SH_PRECEDENCE(T) (_SHPR(T) >> 1)

/*
** |	----------===== private: =====----------
*/

int							map0(t_tokenizer *self);
int							map1(t_tokenizer *self);
int							map2(t_tokenizer *self);
int							map3(t_tokenizer *self);
int							map4(t_tokenizer *self);

# define _1BIT(T) (!((T) & ~0x01))
# define _2BIT(T) (!((T) & ~0x03))
# define _3BIT(T) (!((T) & ~0x07))
# define _4BIT(T) (!((T) & ~0x0f))
# define _5BIT(T) (!((T) & ~0x1f))
# define _8BIT(T) ((T) & 0x80)
# define _XTND(T) ((T) & 0x20)
# define _SHPR(T) ((T) & 0x10 ? 0x10 : T)

#endif
