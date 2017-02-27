/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:06:24 by angagnie          #+#    #+#             */
/*   Updated: 2017/02/25 20:26:07 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATA_H
# define AUTOMATA_H

#include "ft_automaton.h"

typedef e_sh_states		t_sh_states;

enum					e_sh_states
{
	SH_GAP,
	SH_DOLLAR,
	SH_BACKQUOTE,
	SH_COMMENT,

	SH_DEFAULT,
	SH_BACKSLASH,
	SH_SINGLE_QUOTE,
	SH_DOUBLE_QUOTE,
	SH_DQ_BACKSLASH,
	SH_DQ_BACKSLASH_BIS,
}



#endif
