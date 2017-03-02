/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antoine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:45:53 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/02 18:09:56 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ( ) | ; &
** [ - ]
** ---------- Multi-char Operators ----------
0** token  AND_IF    OR_IF    DSEMI
** |       '&&'      '||'     ';;'
** token  DLESS  DGREAT  LESSAND  GREATAND  LESSGREAT  DLESSDASH
** |       '<<'   '>>'    '<&'     '>&'       '<>'       '<<-'
** token  CLOBBER
** |       '>|'
** ---------- reserved words ----------
** token  If    Then    Else    Elif    Fi    Do    Done
** |     'if'  'then'  'else'  'elif'  'fi'  'do'  'done'
** token  Case    Esac    While    Until    For
** |     'case'  'esac'  'while'  'until'  'for'
** These are reserved words, not operator tokens, and are
** recognized when reserved words are recognized.
** token  Lbrace    Rbrace    Bang
**         '{'       '}'       '!'
** token  In
**       'in'
*/

#include "antoine.h"

int		ft_antoine(t_string *input)
{
	t_sstr		output;
	t_dfa		atm[1];

	*atm = dfa_new(input);
	TRANS_ADD(atm, SH_DEFAULT, NEW_TRANS('_', SH_DEFAULT))
	TRANS_ADD(atm, SH_DEFAULT, NEW_TRANS('\\', SH_BACKSLASH));
	TRANS_ADD(atm, SH_DEFAULT, NEW_TRANS('#', SH_COMMENT));
	TRANS_ADD(atm, SH_DEFAULT, NEW_TRANS('\'', SH_SINGLE_QUOTE));
	TRANS_ADD(atm, SH_DEFAULT, NEW_TRANS('"', SH_DOUBLE_QUOTE));
	TRANS_ADD(atm, SH_DEFAULT, NEW_TRANS(' ', SH_GAP));
	TRANS_ADD(atm, SH_DEFAULT, NEW_TRANS('\t', SH_GAP));
	TRANS_ADD();
}
