/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:40:23 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/16 14:33:40 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			exec_list(t_sh_list *self)
{
	void			*ite;
	t_string		str[1];
	t_array			argv;

	argv = NEW_ARRAY(char *);
	ite = ARRAY_ITERATOR(self->nodes);
	while (ARRAY_HASNEXT(self->nodes, ite))
	{
		if (IS_LEAF(ite))
		{
			fta_append(argv, &ARRAY_END(str), 1);
			fta_append(str, ((t_sh_leaf *)ite)->str.data,
					   ((t_sh_leaf *)ite)->str.size);
			fta_append(str, "", 1);
		}
		else
			sh_resolve();

	}
}
