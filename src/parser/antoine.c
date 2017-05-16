/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/16 21:06:36 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** " ` { (
** -> Stack push
** " ` } )
** -> Stack pop
*/

static int		interpret(struct s_pdata *d)
{
	dprintf(2, "interpret\n");
	if (PDATA_TOKEN(d).tag == SH_WORD)
		;
	return (SH_IS_XLEAF(d->tk->current.tag) ?
			extended(d) : ftt_push(self->ast, node_from_token(d));
}

static int		sh__parse(struct s_pdata *d)
{
	int		ret;

	dprintf(2, "sh__parse\n");
	ret = 0;
	while (!ret)
	{
		ret = (PDATA_STATE(d) == SHP_DQUOTE ?
			tk_quote(d->tk) : sh_tokenize(d->tk));
		if (ret)
			return (ret);
		else if (PDATA_TOKEN(d).tag == GAP)
			d->gap = 1;
		else
			interpret(d);
	}
	return (0);
}

int				sh_parse(t_is *in)
{
	struct s_pdata	data;
	t_sh_builder	builder;
	int				ans;

	dprintf(2, "sh_parse\n");
	*data.tk = NEW_TOKENIZER(in);
	*data.stack = NEW_ARRAY(t_sh_context);
	*data.ast = NEW_TREE(t_sh_node, &shell_push);
	builder = NEW_SHBUILDER(SHP_NONE, data.ast->root);
	fta_append(data.stack, &builder, 1);
	ans = sh__parse(&data);
	fta_clear(data.stack);
	ftt_clear(data.ast);
	return (ans);
}

int				ft_antoine(t_string *str)
{
	t_sis	in;

	dprintf(2, "ft_parse(\"%s\")\n", str);
	in = NEW_SIS(str);
	sh_parse((t_is *)&in, w);
	return (0);
}
