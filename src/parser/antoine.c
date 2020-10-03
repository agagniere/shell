/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/06/13 15:13:27 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_printf.h"

/*
** " ` { (
** -> Stack push
** " ` } )
** -> Stack pop
*/

static int		interpret(struct s_pdata *d)
{
	t_sh_node node;

	node = node_from_token(d->tk->current);
	dprintf(2, "Interpreted : %#x\n", node.node.label);
/*
	if (PDATA_TOKEN(d).tag == SH_WORD)
		;
	return (SH_IS_XLEAF(d->tk->current.tag) ?
			extended(d) : ftt_push(d->ast, node_from_token(d->tk.current));
*/
	return (node.node.label ? ftt_push(d->ast, (t_tnode *)&node) : 0);
}

static int		sh__parse(struct s_pdata *d)
{
	int		ret;
	uint8_t	cat;

	dprintf(2, "sh__parse\n");
	ret = 0;
	cat = 0;
	while (!ret)
	{
		ret = (PDATA_STATE(d) == SHP_DQUOTE ?
			tk_dquote(d->tk) : sh_tokenize(d->tk));
		if (d->tk->current.tag == SH_GAP)
			cat = 0;
		else if (cat < 2)
			cat ++;
		/* \/ Debug \/ */
		if (ret)
			dprintf(2, "END\n");
		else {
			if (SH_IS_FLEAF(d->tk->current.tag))
				dprintf(2, "%s(\"%.*s\", %#x)%s %hhu\n", PURPLE,
						(int)d->tk->current.data.len, d->tk->current.data.str,
						d->tk->current.tag, EOC, cat);
			else
				dprintf(2 , "%s(%i, %#x)%s %hhu\n", BOLD_PURPLE,
						d->tk->current.tag, d->tk->current.tag, EOC, cat);
		}
		/* /\ Debug /\ */
		if (!ret && (cat == 1))
			ret = interpret(d);
	}
	ftt_debug(d->ast);
	return (ret);
}

int				sh_parse(t_is *in)
{
	struct s_pdata	data;
	t_sh_builder	builder;
	int				ans;

	ft_putendl_fd(__FUNCTION__, 2);
	*data.tk = NEW_TOKENIZER(in);
	*data.stack = NEW_ARRAY(t_sh_context);
	*data.ast = NEW_TREE(t_sh_node, &shell_push);
	builder = NEW_SHBUILDER(SHP_NONE, data.ast->root);
	fta_append(data.stack, &builder, 1);
	ans = sh__parse(&data);
	dprintf(2, "--\n");
	fta_clear(data.stack);
	dprintf(2, "---\n");
//	ftt_clear((t_tree **)&data.ast);
	dprintf(2, "----\n");
	return (ans);
}

int				ft_antoine(t_string *str)
{
	t_sis	in;

	dprintf(2, "ft_antoine(\"%.*s\")\n", str->size, str->data);
	in = NEW_SIS(str);
	return (sh_parse((t_is *)&in));
}
