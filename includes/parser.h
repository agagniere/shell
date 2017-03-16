/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:30:00 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/16 16:41:41 by angagnie         ###   ########.fr       */
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
typedef struct s_sh_context		t_sh_context;
typedef enum e_sh_state			t_sh_state;
typedef enum e_sh_layer			t_sh_layer;
typedef union u_sh_node			t_sh_node;

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

enum                    e_sh_state
{
	SHS_START,
	SHS_ARGS
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
	int				(*exec)(t_sh_operator *);
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

struct						s_sh_context
{
	t_sh_layer		name;
	t_tnode			*root;
};

t_tr						shell_push(t_tnode **a, t_tnode *b);

# define NEW_OP(LABEL,F) (t_sh_operator){NEW_NODE(LABEL), F}

# define NEW_RD(LBL,FD,FLG) (t_sh_redirection){NEW_OP(LBL, &exec_rdf), FD, FLG}

# define NEW_SHCONTEXT(NAME,ROOT) (t_sh_context){NAME, ROOT}

# define OP_SEMI NEW_OP(SH_SEMI, &exec_semi)
# define OP_AMPER NEW_OP(SH_AMPER, &exec_amper)
# define OP_AND_IF NEW_OP(SH_AND, &exec_andif)
# define OP_OR_IF NEW_OP(SH_OR, &exec_orif)
# define OP_PIPE NEW_OP(SH_PIPIE, &exec_pipe)

# define RD_LEFT NEW_RD(SH_LEFT, 0, O_RDONLY)
# define RD_RIGHT NEW_RD(SH_RIGHT, 1, O_CREAT | O_WRONLY | O_EXCL)
# define RD_CLOBBER NEW_RD(SH_CLOBBER, 1, O_CREAT | O_WRONLY)
# define RD_APPEND NEW_RD(SH_APPEND, 1, O_CREAT | O_WRONLY | O_APPEND)
# define RD_RW NEW_RD(SH_RW, 0, O_CREAT | O_RDWR)

#endif
