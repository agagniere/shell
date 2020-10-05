/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 18:02:06 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/23 15:26:52 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_sh_node
	op_from_token(t_token token)
{
	if (token.tag == SH_SEMI)
		return (t_sh_node){.op = OP_SEMI};
	else if (token.tag == SH_AMPER)
		return (t_sh_node){.op = OP_AMPER};
	else if (token.tag == SH_AND)
		return (t_sh_node){.op = OP_AND_IF};
	else if (token.tag == SH_OR)
		return (t_sh_node){.op = OP_OR_IF};
	else if (token.tag == SH_PIPE)
		return (t_sh_node){.op = OP_PIPE};
//	return (){};
}

static t_sh_node
	rd_from_token(t_token token)
{
	if (token.tag == SH_RIGHT)
		return (t_sh_node){.rd = RD_RIGHT};
	else if (token.tag == SH_CLOBBER)
		return (t_sh_node){.rd = RD_CLOBBER};
	else if (token.tag == SH_APPEND)
		return (t_sh_node){.rd = RD_APPEND};
	else if (token.tag == SH_LEFT)
		return (t_sh_node){.rd = RD_LEFT};
	else if (token.tag == SH_RW)
		return (t_sh_node){.rd = RD_RW};
//	else if (SH_HEREDOC <= token.tag && token.tag <= SH_HERESTR)
//		return (heredoc(token.tag));
}

static t_sh_node
	leaf_from_token(t_token token)
{
	if (SH_IS_FLEAF(token.tag))
		return (t_sh_node){.leaf = NEW_LEAF(token.data, token.tag)};
}

t_sh_node
	node_from_token(t_token token)
{
	if (0 < token.tag && token.tag <= 0x08)
		return (op_from_token(token));
	else if (0x10 <= token.tag && token.tag < 0x80)
		return (rd_from_token(token));
	else if (token.tag & (1 << 7))
		return (leaf_from_token(token));
}
