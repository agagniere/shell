/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:30:00 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/25 06:32:04 by angagnie         ###   ########.fr       */
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
	SHP_QUOTE,
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
	t_string		str;
};

union						u_sh_node
{
	t_tnode				node;
	t_sh_operator		op;
	t_sh_redirection	rd;
	t_sh_list			list;
	t_sh_clause			clause;
};

struct						s_sh_builder
{
	t_sh_layer		name;
	t_tnode			*root;
};

struct						s_sh_context
{
	t_array			aliases[1];
	t_array			variables[1];
	t_array			functions[1];
};

struct						s_pdata
{
	t_is			*in;
	t_sh_builder	builder;
	t_array			stack[1];
	t_tokenizer		tk[1];
	t_tree			ast[1];
};

t_tr						shell_push(t_tnode **a, t_tnode *b);
t_string					sh_resolve(t_sh_node *self, t_sh_context *w);

# define NEW_OP(LABEL,P,E) (t_sh_operator){NEW_NODE(LABEL), P, E}

# define NEW_RD(L,F,I) (t_sh_redirection){NEW_OP(L, shpush_rdrc, exec_rdf), F, I}

# define NEW_SHBUILDER(NAME,ROOT) (t_sh_niu){NAME, ROOT}

# define NEW_SHLIST (t_sh_list){NEW_OP(SH_LIST, &shpush_list)}

# define OP_SEMI NEW_OP(SH_SEMI, &shpush_node, &exec_semi)
# define OP_AMPER NEW_OP(SH_AMPER, &shpush_node, &exec_amper)
# define OP_AND_IF NEW_OP(SH_AND, &shpush_node, &exec_andif)
# define OP_OR_IF NEW_OP(SH_OR, &shpush_node, &exec_orif)
# define OP_PIPE NEW_OP(SH_PIPIE, &shpush_node, &exec_pipe)
# define OP_SHLIST NEW_OP(SH_LIST, &shpush_list, &exec_list)

# define RD_LEFT NEW_RD(SH_LEFT, 0, O_RDONLY)
# define RD_RIGHT NEW_RD(SH_RIGHT, 1, O_CREAT | O_WRONLY | O_EXCL)
# define RD_CLOBBER NEW_RD(SH_CLOBBER, 1, O_CREAT | O_WRONLY)
# define RD_APPEND NEW_RD(SH_APPEND, 1, O_CREAT | O_WRONLY | O_APPEND)
# define RD_RW NEW_RD(SH_RW, 0, O_CREAT | O_RDWR)

#endif
