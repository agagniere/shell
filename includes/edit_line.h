/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:14:48 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/09 19:10:03 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/ioctl.h>
#include <term.h>
#include <curses.h>


typedef void				(*t_spe_key) (t_line *l);

typedef struct				s_actions
{
	t_spe_key				action;
	int						value[6];
	char					*key;
}							t_actions;

int			ft_reset_term(void);
int			ft_init_term(void);
void		ft_right(t_line *l);
void		ft_left(t_line *l);
