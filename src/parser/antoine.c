/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/19 15:09:16 by angagnie         ###   ########.fr       */
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
	t_sh_node node;

	dprintf(2, "interpret\n");
	node = node_from_token(d->tk->current);
/*	if (PDATA_TOKEN(d).tag == SH_WORD)
		;
	return (SH_IS_XLEAF(d->tk->current.tag) ?
			extended(d) : ftt_push(d->ast, node_from_token(d->tk.current));
*/
	return (ftt_push(d->ast, (t_tnode *)&node));
}

static int		sh__parse(struct s_pdata *d)
{
	int		ret;

	dprintf(2, "sh__parse\n");
	ret = 0;
	while (!ret)
	{
		ret = (PDATA_STATE(d) == SHP_DQUOTE ?
			tk_dquote(d->tk) : sh_tokenize(d->tk));
		if (d->tk->current.tag == SH_WORD || d->tk->current.tag == SH_TEXT)
			dprintf(2, "%s(\"%.*s\", %i)%s\n", PURPLE,
					(int)d->tk->current.data.len, d->tk->current.data.str,
					d->tk->current.tag, EOC);
		else
			dprintf(2 , "%s(%i, %#x)%s\n", BOLD_PURPLE,
					d->tk->current.tag, d->tk->current.tag, EOC);
		if (ret)
			return (ret);
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
	ftt_clear((t_tree **)&data.ast);
	return (ans);
}

int				ft_antoine(t_string *str)
{
	t_sis	in;

	dprintf(2, "ft_antoine(\"%s\")\n", str->data);
	in = NEW_SIS(str);
	return (sh_parse((t_is *)&in));
}
