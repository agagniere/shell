/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/17 17:25:50 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"

int		tk_accept(t_tokenizer *self, char c)
{

}

int		tk_next(t_tokenizer *self)
{

}

int		sh_parse(t_is *in, t_sh_context *w)
{
	t_array			stack[1];
	t_tokenizer		tk[1];
	t_tree			ast[1];

	*tk = NEW_TOKENIZER(in);
	*stack = NEW_ARRAY(t_sh_context);
	*ast = NEW_TREE(t_sh_node);
	fta_append(stack, &NEW_SHCONTEXT(SHP_NONE, ast->root), 1);
	while (!tk->eof)
		tk_next(tk);
}

int		ft_antoine(t_string *str, t_sh_context *w)
{
	t_sis	in;

	in = NEW_SIS(str)
		sh_parse((t_is *)&in, w);
	return (0);
}
