/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:30:00 by angagnie          #+#    #+#             */
/*   Updated: 2017/02/09 23:36:34 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_tree.h"

typedef enum e_operator		t_operator;
typedef struct s_shell_node	t_shell_node;

enum						e_operator
{
	OP_NA,
	OP_PIPE,
	OP_AND,
	OP_OR,
	OP_SEMI,
	OP_AMPER,

	OP_SEMICOLON = OP_SEMI,
	OP_AMPERSAND = OP_AMPER
};

struct						s_shell_node
{
	t_node		super;
	t_operator	name;
};

struct						s_shell_leaf
{
	t_node		super;
	t_string	cmd;
};

# define PRECEDENCE(O) ((O) >> 1)

int							shell_push(t_node **a, t_node *b);

#endif
