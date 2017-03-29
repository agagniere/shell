/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/29 02:35:51 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		sh__parse(struct s_pdata *d)
{
	d->tk->in->refresh(d->tk->in);
}

int		sh_parse(t_is *in, t_sh_context *w)
{
	struct s_pdata	data;
	t_sh_builder	builder;

	*data.tk = NEW_TOKENIZER(in);
	*data.stack = NEW_ARRAY(t_sh_context);
	*data.ast = NEW_TREE(t_sh_node, &shell_push);
	builder = NEW_SHBUILDER(SHP_NONE, data.ast->root);
	fta_append(data.stack, &builder, 1);
	return (sh__parse(&data));
}

int		ft_antoine(t_string *str, t_sh_context *w)
{
	t_sis	in;

	in = NEW_SIS(str);
	sh_parse((t_is *)&in, w);
	return (0);
}
