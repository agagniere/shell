/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:06:24 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/13 16:49:57 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATA_H
# define AUTOMATA_H

#include "ft_automaton.h"

typedef e_sh_states		t_sh_states;

enum					e_sh_states
{
	SHS_GAP,
	SHS_DOLLAR,
	SHS_BACKQUOTE,
	SHS_COMMENT,

	SHS_DEFAULT,
	SHS_BACKSLASH,
	SHS_SINGLE_QUOTE,
	SHS_DOUBLE_QUOTE,
	SHS_DQ_BACKSLASH,
	SHS_DQ_BACKSLASH_BIS,
}

#endif
