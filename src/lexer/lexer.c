/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/18 21:41:33 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		tk_accept(t_tokenizer *self, char c)
{

}

int		tk_next(t_tokenizer *self)
{

}

int		sh__parse(struct s_pdata d)
{
}

int		sh_parse(t_is *in, t_sh_context *w)
{
	struct s_pdata	data;

	*data.tk = NEW_TOKENIZER(in);
	*data.stack = NEW_ARRAY(t_sh_context);
	*data.ast = NEW_TREE(t_sh_node);
	fta_append(data.stack, &NEW_SHCONTEXT(SHP_NONE, ast->root), 1);
}

int		ft_antoine(t_string *str, t_sh_context *w)
{
	t_sis	in;

	in = NEW_SIS(str);
	sh_parse((t_is *)&in, w);
	return (0);
}
