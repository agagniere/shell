/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antoine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:45:53 by angagnie          #+#    #+#             */
/*   Updated: 2017/02/21 20:07:41 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ---------- Operators ----------
** token  AND_IF    OR_IF    DSEMI
** |       '&&'      '||'     ';;'
** token  DLESS  DGREAT  LESSAND  GREATAND  LESSGREAT  DLESSDASH
** |       '<<'   '>>'    '<&'     '>&'      '<>'       '<<-'
** token  CLOBBER
**          '>|'
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


int		ft_antoine(t_string *input)
{
	t_string	clean;
	t_auto		dfa;

	// TODO : Handle exclamation marks

}
