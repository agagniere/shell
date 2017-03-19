/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:50:15 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/19 15:06:24 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENIZER_H
# define SH_TOKENIZER_H

# include "ft_token.h"

typedef enum e_sh_token		t_sh_token;

enum						e_sh_token
{
	SH_SEMI, //		;
	SH_AMPER, //	&	0

	SH_AND, //		&&	1
	SH_OR, //		||

	SH_PIPE, //		|	2

	SH_RIGHT = 0x10,//>	4
	SH_CLOBBER, //	>|
	SH_DRIGHT, //	>>
	SH_LEFT, //		<
	SH_DLEFT, //	<<
	SH_DLEFTD, //	<<-
	SH_TLEFT, //	<<<
	SH_LR, //		<>
	SH_RIGHTAND, // >&
	SH_LEFTAND, //	<&

	SH_CLOBBERB, //	>!
	SH_PIPEAND, //	|&
	SH_ANDRIGHT, //	&>

	SH_WORD = 0x80,
	SH_TEXT,
	SH_IONUMBER,

	SH_SEMICOLON = SH_SEMI,
	SH_AMPERSAND = SH_AMPER,
	SH_APPEND = SH_DRIGHT,
	SH_HEREDOC = SH_DLEFT,
	SH_HEREDOCT = SH_DLEFTD,
	SH_HERESTR = SH_TLEFT,
	SH_RW = SH_LR,

	SH_LIST = 0x90,
	SH_SUBS,
};

/*
** |	----------===== public: =====----------
*/

# define SH_IS_SEPARATOR(T) _1BIT(T)
# define SH_IS_LOGICAL(T) (_2BIT(T) && !_1BIT(T))
# define SH_IS_REDIRECTION(T) (_5BIT(T) && !_4BIT(T))
# define SH_IS_FLEAF(T) (_8BIT(T) && !_XTND(T))
# define SH_IS_XLEAF(T) (_8BIT(T) && _XTND(T))

/*
** |	----------===== private: =====----------
*/

# define _1BIT(T) (!((T) & ~0x01))
# define _2BIT(T) (!((T) & ~0x03))
# define _3BIT(T) (!((T) & ~0x07))
# define _4BIT(T) (!((T) & ~0x0f))
# define _5BIT(T) (!((T) & ~0x1f))
# define _8BIT(T) ((T) & 0x80)
# define _XTND(T) ((T) & 0x10)

#endif
