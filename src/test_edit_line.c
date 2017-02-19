/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_edit_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:00:53 by malaine           #+#    #+#             */
/*   Updated: 2017/02/14 18:37:15 by malaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include <stdio.h>

void	check_nb_line(int *pos_rtn)
{
	int count = 14;
	int index = 0;

	while (pos_rtn[index] < count)
		index++;

	printf("vous etes sur la ligne : %d\n", index + 1);
}

void	check_rtn(t_line *l)
{
/*	int nb_rtn;
	int pos_rtn[10];
	int size_str[10];
	int i = 0;
	int ii = 0;
	int iii = 0;*/

	void    *ite;

    ite = ARRAY_GET(&l->str, -1);
	while (ARRAY_HASNEXT(&l->str, ite))
    {
		if (*(char *)ite == '\n')
		{
			fta_append(&g_multi.pos_rtn, &g_multi.index1, 1);
			fta_append(&g_multi.size_str, &g_multi.index3, 1);
//			pos_rtn[ii] = g_multi->index1;
//            size_str[ii] = g_multi->index3;
//			g_multi->index2++;
			g_multi.index3 = 0;
			g_multi.nb_rtn++;
			
		}
		g_multi.index3++;
		g_multi.index1++;
	}
	fta_append(&g_multi.size_str, &g_multi.index3, 1);
//	size_str[ii] = g_multi->index3;

/*	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			pos_rtn[ii] = i;
			size_str[ii] = iii;
			ii++;
			iii = 0;
			nb_rtn++;
		}
		iii++;
		i++;
	}
	size_str[ii] = iii;*/

//	check_nb_line(g_line->pos_rtn);
	do_term("sc");
    do_goto("DO", 0, 5);
    do_term("cd");
    do_goto("DO", 0, 5);
	int *tamere = g_multi.pos_rtn.data;
	int *fuck = g_multi.size_str.data;
	printf("nombre de ligne : %d\n", g_multi.nb_rtn);
	size_t a  = 0;
	while (a < g_multi.pos_rtn.size)
	{
		printf("%d\n", tamere[a]);
		a++;
	}
	do_term("rc");
}

