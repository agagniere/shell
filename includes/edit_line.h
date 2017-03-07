/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:14:48 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/07 17:37:33 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/ioctl.h>
#include <term.h>
#include <curses.h>
#include "multi_line.h"

typedef void				(*t_spe_key) (t_line *l);

typedef struct				s_actions
{
	t_spe_key				action;
	int						value[6];
	char					*key;
}							t_actions;

void		put_cursor(t_line *l);
void		ft_autocomp(t_line *line);
void        ft_down(t_line *l);
void        ft_up(t_line *l);
void		ft_ctrl_d(t_line *l);
void		ft_ctrl_l(t_line *l);
void        ft_ctrl_down(t_line *l);
void        ft_ctrl_up(t_line *l);
void        ft_delete(t_line *l);
void        ft_backspace(t_line *l);
void        ft_paste(t_line *l);
void        ft_cut(t_line *l);
void    check_rtn(t_line *l);
void		check_is_space_r(t_line *l);
void		check_space_r(t_line *l);
void		check_space_l(t_line *l);
void		check_is_space_l(t_line *l);
int			check_last_word(t_line *l);
int			check_first_word(t_line *l);
void        ft_ctrl_left(t_line *l);
void        ft_ctrl_right(t_line *l);
int         do_goto(char *key, int col, int row);
int         actions(t_line *l);
void        go_up(t_line *l);
void        go_down(t_line *l);
void        print(t_line *l);
void        ft_home(t_line *l);
void        ft_end(t_line *l);
int			do_term(char *key);
int			ft_reset_term(void);
int			ft_init_term(void);
void		ft_right(t_line *l);
void		ft_left(t_line *l);
