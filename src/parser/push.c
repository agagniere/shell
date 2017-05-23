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
	t_sh_node ans;

	ft_bzero(&ans, sizeof(ans));
	if (token.tag == SH_SEMI)
		ans.op = OP_SEMI;
	else if (token.tag == SH_AMPER)
		ans.op = OP_AMPER;
	else if (token.tag == SH_AND)
		ans.op = OP_AND_IF;
	else if (token.tag == SH_OR)
		ans.op = OP_OR_IF;
	else if (token.tag == SH_PIPE)
		ans.op = OP_PIPE;
	return (ans);
}

static t_sh_node
	rd_from_token(t_token token)
{
	t_sh_node ans;

	ft_bzero(&ans, sizeof(ans));
	if (token.tag == SH_RIGHT)
		ans.rd = RD_RIGHT;
	else if (token.tag == SH_CLOBBER)
		ans.rd = RD_CLOBBER;
	else if (token.tag == SH_APPEND)
		ans.rd = RD_APPEND;
	else if (token.tag == SH_LEFT)
		ans.rd = RD_LEFT;
	else if (token.tag == SH_RW)
		ans.rd = RD_RW;
//	else if (SH_HEREDOC <= token.tag && token.tag <= SH_HERESTR)
//		return (heredoc(token.tag));
	return (ans);
}

static t_sh_node
	leaf_from_token(t_token token)
{
	t_sh_node ans;

	ft_bzero(&ans, sizeof(ans));
	if (SH_IS_FLEAF(token.tag))
		ans.leaf = NEW_LEAF(token.data, token.tag);
	return (ans);
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
