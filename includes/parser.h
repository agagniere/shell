/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:30:00 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/14 10:21:32 by angagnie         ###   ########.fr       */
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
typedef struct s_sh_context		t_sh_context;
typedef enum e_sh_layer			t_sh_layer;

enum						e_sh_layer
{
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
	t_sh_token		name;
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
	t_tnode			super;
	t_array			nodes;
};

struct						s_sh_clause
{
	t_tnode			super;
};

struct						s_sh_context
{
	t_sh_layer		name;
	t_tnode			*root;
};

t_tr						shell_push(t_node **a, t_node *b);

#endif
