/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 22:30:00 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/13 17:20:05 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_tree.h"

typedef struct s_shell_node	t_shell_node;

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
};

struct						s_sh_redirection
{
	t_sh_operator	super;
	int				filedes;
};

struct						s_shell_node
{
	t_tnode		super;
	union
	{
		t_operator	name;
	}			data;
};

# define PRECEDENCE(O) ((O) >> 1)

t_tr						shell_push(t_node **a, t_node *b);

#endif
