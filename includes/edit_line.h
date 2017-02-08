/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:14:48 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/08 18:52:24 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/ioctl.h>

typedef void				(*t_spe_key) (t_line *l);

typedef struct				s_actions
{
	t_spe_key				action;
	int						value[6];
	char					*key;
}							t_actions;

int             actions(t_line *l);
int             key_is_special(t_line *l);
void            ctrl_r(t_line *l);
void            ft_real_backspace(t_line *l);
void            ft_backspace(t_line *l);
void            ft_right(t_line *l);
void            ft_left(t_line *l);
void            ft_ctrl_down(t_line *l);
void            ft_ctrl_up(t_line *l);
void            ft_paste(t_line *l);
void            ft_cut(t_line *l);
void            ft_home(t_line *l);
void            ft_end(t_line *l);
void            ft_ctrl_right(t_line *l);
void            ft_ctrl_left(t_line *l);
void            ft_autocomp(t_line *l);
void            ft_up(t_line *l);
void            ft_down(t_line *l);
void            ft_bp(t_line *l);
void            ft_fw(t_line *l);
void            get_line_history(t_line *l, t_ftl_root *root);
int             get_nbline(t_line *l);
void            ft_ctrl_l(t_line *l);
void            ft_ctrl_d(t_line *l);
void            ft_ctrl_a(t_line *l);
void            ft_ctrl_e(t_line *l);

