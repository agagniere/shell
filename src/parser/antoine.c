/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/10 19:19:52 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		sh__parse(struct s_pdata *d)
{
	int		ret;

	ret = 0;
	while (!ret)
	{
		ret = sh_tokenize(d->tk);
		if (ret == 2)
			/* Quote interrupted */;
			/* Put 'quote' in the stack*/
		else if (ret == 3)
			/* BSlash */;
			/* Prompt for next line and remove the two characters '\\' and '\n' */
		else if (ret == 0)
			/* Fine !! */;
			/* act accordingly bucko */
		else
			printf("WTF !\n");
	}
	return (0);
}

int				sh_parse(t_is *in)
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

int				ft_antoine(t_string *str)
{
	t_sis	in;

	in = NEW_SIS(str);
	sh_parse((t_is *)&in, w);
	return (0);
}
