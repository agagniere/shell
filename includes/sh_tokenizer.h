/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:50:15 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/13 19:39:50 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENIZER
# define SH_TOKENIZER

typedef enum e_sh_token		t_sh_token;

enum						e_sh_token
{
	SH_SEMI, //		;	0
	SH_AMPER, //	&

	SH_AND, //		&&	1
	SH_OR, //		||

	SH_PIPE, //		|	2

	SH_RIGHT = 8,//	>	3
	SH_CLOBBER, //	>|
	SH_DRIGHT, //	>>
	SH_LEFT, //		<
	SH_DLEFT, //	<<
	SH_DLEFTD, //	<<-
	SH_TLEFT, //	<<<
	SH_LR, //		<>
	SH_RIGHTAND, // >&
	SH_LEFTAND, //	<&
	SH_PIPEAND, //	|&

	SH_WORD = (1 << 7),
	SH_TEXT,
	SH_IONUMBER,

	SH_SEMICOLON = SH_SEMI,
	SH_AMPERSAND = SH_AMPER,
	SH_APPEND = SH_DRIGHT,
	SH_HEREDOC = SH_DLEFT,
	SH_HEREDOCT = SH_DLEFTD,
	SH_HERESTR = SH_TLEFT,
	SH_RW = SH_LR,
};

#endif
