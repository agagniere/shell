/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/11 23:16:13 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		interpret(struct s_pdata *d)
{
	if (d->tk->current.tag & (1 << 7))
		;
}

static int		sh__parse(struct s_pdata *d)
{
	int		ret;

	ret = 0;
	while (!ret)
	{
		ret = (PDATA_STATE(d) == SHP_DQUOTE ?
			tk_quote(d->tk) : sh_tokenize(d->tk));
		if (ret == 0)
			return (interpret(d));
		else
			return (ret);
	}
	return (0);
}

int				sh_parse(t_is *in)
{
	struct s_pdata	data;
	t_sh_builder	builder;
	int				ans;

	*data.tk = NEW_TOKENIZER(in);
	*data.stack = NEW_ARRAY(t_sh_context);
	*data.ast = NEW_TREE(t_sh_node, &shell_push);
	builder = NEW_SHBUILDER(SHP_NONE, data.ast->root);
	fta_append(data.stack, &builder, 1);
	ans = sh__parse(&data);

	return (ans);
}

int				ft_antoine(t_string *str)
{
	t_sis	in;

	in = NEW_SIS(str);
	sh_parse((t_is *)&in, w);
	return (0);
}
