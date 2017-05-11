/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:30:00 by angagnie          #+#    #+#             */
/*   Updated: 2017/05/11 21:41:59 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_tree.h"
# include "sh_tokenizer.h"
# include "libft.h"

typedef struct s_sh_operator	t_sh_operator;
typedef struct s_sh_redirection	t_sh_redirection;
typedef struct s_sh_list		t_sh_list;
typedef struct s_sh_clause		t_sh_clause;
typedef struct s_sh_leaf		t_sh_leaf;
typedef enum e_sh_state			t_sh_state;
typedef enum e_sh_layer			t_sh_layer;
typedef union u_sh_node			t_sh_node;
typedef struct s_sh_context		t_sh_context;
typedef struct s_sh_builder		t_sh_builder;

enum						e_sh_layer
{
	SHP_NONE,
	SHP_CURSH,
	SHP_SUBSH,
	SHP_IF,
	SHP_THEN,
	SHP_ELSE,
	SHP_DQUOTE,
	SHP_BQUOTE,
	SHP_DO,
	SHP_WHILE
};

enum						e_sh_state
{
	SHS_START,
	SHS_ARGS,
	SHS_CAT
};

/*
** --- Reserved words ---
** if then else elif fi
** do done
** case esac
** while until
** for in
** ----------------------
** { } !
** ( ) $
** [ ] -
** %
** [ = test
** [[ = builtin
*/

struct						s_sh_operator
{
	t_tnode			super;
	int				(*const push)(t_tnode **, t_tnode *);
	int				(*const exec)(t_sh_operator *, t_sh_context *);
//	t_string		(*const resolve)(t_sh_operator *);
};

struct						s_sh_redirection
{
	t_sh_operator	super;
	int				filedes;
	int				flags;
};

struct						s_sh_list
{
	t_sh_operator	super;
	t_array			nodes[1];
};

struct						s_sh_clause
{
	t_sh_list		super;
};

struct						s_sh_leaf
{
	t_tnode			super;
	t_substr		str;
};

union						u_sh_node
{
	t_tnode				node;
	t_sh_operator		op;
	t_sh_redirection	rd;
	t_sh_list			list;
	t_sh_clause			clause;
	t_sh_leaf			leaf;
};

struct						s_sh_builder
{
	t_sh_layer		name;
	t_tnode			*root;
};

struct						s_sh_context
{
	int				*ret;
	t_array			aliases[1];
	t_array			variables[1];
};

struct						s_pdata
{
	t_array			stack[1];
	t_tokenizer		tk[1];
	t_tree			ast[1];
};

t_tr						shell_push(t_tnode **a, t_tnode *b);
t_string					sh_resolve(t_sh_node *self, t_sh_context *w);

int							exec_semi(t_sh_operator *self, t_sh_context *w);
int							exec_amper(t_sh_operator *self, t_sh_context *w);
int							exec_andif(t_sh_operator *self, t_sh_context *w);
int							exec_orif(t_sh_operator *self, t_sh_context *w);
int							exec_pipe(t_sh_operator *self, t_sh_context *w);
int							exec_rd(t_sh_operator *self, t_sh_context *w);
int							exec_rdf(t_sh_operator *self, t_sh_context *w);
int							exec_list(t_sh_operator *self, t_sh_context *w);

t_tr						shpush_node(t_tnode **self, t_tnode *new);
t_tr						shpush_rdrc(t_tnode **self, t_tnode *new);
t_tr						shpush_list(t_tnode **self, t_tnode *new);

# define NEW_LEAF(STR) (t_sh_leaf){NEW_NODE(SH_WORD), STR}

# define NEW_OP(LABEL,P,E) (t_sh_operator){NEW_NODE(LABEL), P, E}

# define NEW_RD(L,F,I) (t_sh_redirection){NEW_OP(L, shpush_rdrc, exec_rdf), F, I}

# define NEW_SHBUILDER(NAME,ROOT) (t_sh_builder){NAME, ROOT}

# define NEW_SHLIST (t_sh_list){_NEW_SHLIST, {NEW_ARRAY(t_sh_node *)}}
# define _NEW_SHLIST NEW_OP(SH_LIST, &shpush_list, &exec_list)

/*
** Nodes
*/

# define OP_SEMI NEW_OP(SH_SEMI, &shpush_node, &exec_semi)
# define OP_AMPER NEW_OP(SH_AMPER, &shpush_node, &exec_amper)

# define OP_AND_IF NEW_OP(SH_AND, &shpush_node, &exec_andif)
# define OP_OR_IF NEW_OP(SH_OR, &shpush_node, &exec_orif)

# define OP_PIPE NEW_OP(SH_PIPE, &shpush_node, &exec_pipe)

# define OP_SHLIST NEW_OP(SH_LIST, &shpush_list, &exec_list)

# define RD_LEFT NEW_RD(SH_LEFT, 0, O_RDONLY)
# define RD_RIGHT NEW_RD(SH_RIGHT, 1, O_CREAT | O_WRONLY | O_EXCL)
# define RD_CLOBBER NEW_RD(SH_CLOBBER, 1, O_CREAT | O_WRONLY)
# define RD_APPEND NEW_RD(SH_APPEND, 1, O_CREAT | O_WRONLY | O_APPEND)
# define RD_RW NEW_RD(SH_RW, 0, O_CREAT | O_RDWR)

# define NODE_PRECEDENCE(N) SH_PRECEDENCE(((t_tnode *)(N))->label)

# define PDATA_CURRENT(D) (ARRAY_GETT(t_sh_builder, (D)->stack, (D)->size - 1))
# define PDATA_SATE(D) (PDATA_CURRENT(D)->name)

#endif
