/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:29:03 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/09 16:51:36 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomp.h"

static t_actions const g_actions[1] = {
	{NULL, {9, 0, 0, 0, 0, 0}, "TAB"},
};

static void			my_read(t_line *l, int *first_time)
{
	ft_bzero(l->buffer, 6);
	if (*first_time == 0 && (*first_time = 1))
		l->buffer[0] = 9;
	else
		read(STDIN_FILENO, l->buffer, 6);
}

static int			cmp_buf(int *value, char *buf)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (buf[i] != value[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t		get_end_erase(t_line *line)
{
	size_t		i;
	char		*ptr;

	ptr = line->str.data;
	i = line->cursor;
	while (i < line->str.size && ptr[i] != '/' && ptr[i] != ' ')
		i++;
	if (ptr[i] == ' ' || ptr[i] == '/')
		i--;
	return (i);
}

static size_t		get_start_erase(t_line *line)
{
	size_t		i;
	char		*ptr;

	ptr = line->str.data;
	i = line->cursor;
	while (i > 0 && ptr[i] != '/' && ptr[i] != ' ')
		i--;
	if (ptr[i] == ' ' || ptr[i] == '/')
		i++;
	return (i);
}

static void		replace_auto(t_line *line, t_autocomp *autocomp)
{
	t_string	*tmp;
	size_t		end;
	size_t		start;
	size_t		len;

	start = get_start_erase(line);
	end = get_end_erase(line);
	//printf("\nstart = [%d] ; end = [%d]\n", start, end);
	len = end - start;
//	if (i > line->cursor)
//	{
		fta_popindex(&line->str, start, len);
		tmp = ARRAY_GETT(t_string, &autocomp->tab_a, autocomp->index);
	//	printf("\n{%s}\n", (char *)line->str.data);
		fta_insert(&line->str, tmp->data, tmp->size, start);
//	}
		STR_NULL_TERMINATE(&line->str);
		line->sauv_cursor = line->str.size;
		//line->cursor = start;
}

static void		do_autocomp(t_line *line, t_autocomp *autocomp)
{
	while (1)
	{
		my_read(line, &autocomp->first_time);
		if (cmp_buf((int *)g_actions[0].value, line->buffer) == 0)
		{
			if (autocomp->index == autocomp->tab_a.size)
				autocomp->index = 0;
			line->sauv_cursor = line->cursor;
			replace_auto(line, autocomp);
		//	printf("\n%s\n",(char *)line->str.data);
			ft_home(line);
			print(line);
			//ft_end(line);
			print_auto(line, autocomp);

		//	printf("%s\n",(char *)line->str.data);
			autocomp->index++;
		}
		else
		{
			actions(line);
			break ;
		}
	}
}

static void		prepare_ptr(t_line *line, char **ptr, char **ptr2)
{
	t_string	tmp;
	size_t		i;

	tmp = fta_new(sizeof(char));
	*ptr = (char *)line->str.data;
	i = line->cursor;
	while (i > 0 && (*ptr)[i] != ' ')
		i--;
	(*ptr)[i] == ' ' ? i++ : 0;
	*ptr = *ptr + i;
	STR_JOIN_CS(&tmp, *ptr, line->cursor - i);
	STR_NULL_TERMINATE(&tmp);
	*ptr2 = ft_strrchr(tmp.data ,'/');
	if (*ptr2 == NULL)
	{
		*ptr2 = (char *)line->str.data + i;
		*ptr = ".";
	}
	else
	{
		if (**(ptr2) == '/' && tmp.data == *ptr2)
			*ptr = "/";
		**ptr2 = '\0';
		*ptr2 = *ptr2 + 1;
	}
}


static void		init_str(t_autocomp *autocomp, t_line *line)
{
	char		*ptr;
	char		*ptr2;

	STR_NULL_TERMINATE(&line->str);
	prepare_ptr(line, &ptr, &ptr2);
	STR_JOIN_CS(&autocomp->path, ptr, ft_strlen(ptr));
	STR_JOIN_CS(&autocomp->str, ptr2, ft_strlen(ptr2));
	STR_NULL_TERMINATE(&autocomp->path);
	STR_NULL_TERMINATE(&autocomp->str);
}

int				create_tab_a(t_autocomp *autocomp)
{
	t_aut_info		info;
	t_string		tmp;

	tmp = NEW_STRING;
	if ((info.dirp = opendir((char *)autocomp->path.data)) != NULL)
	{
		while ((info.dp = readdir(info.dirp)) != NULL)
		{
			if (!(info.dp->d_name[0] == '.' && ((char*)autocomp->str.data)[0] == '\0'))
				if (ft_strncmp(info.dp->d_name, ".", 1) != 0
						&& ft_strncmp(info.dp->d_name, "..", 2) != 0
						&& ft_strncmp(info.dp->d_name,
							(char *)autocomp->str.data, autocomp->str.size) == 0)
				{
					STR_JOIN_CS(&tmp, info.dp->d_name,
							ft_strlen(info.dp->d_name));
					STR_NULL_TERMINATE(&tmp);
					fta_append(&autocomp->tab_a, &tmp, 1);
					tmp = NEW_STRING;
				}
		}
		closedir(info.dirp);
	}
	return (0);
}

static void		autocomp_init(t_autocomp *autocomp)
{
	autocomp->tab_a = NEW_ARRAY(t_string);
	autocomp->path = fta_new(sizeof(char));
	autocomp->str = fta_new(sizeof(char));
	autocomp->first_time = 0;
	autocomp->index = 0;
	autocomp->nl = 0;
}

void			ft_autocomp(t_line *line)
{
	t_autocomp	autocomp;

	autocomp_init(&autocomp);
	init_str(&autocomp, line);
	create_tab_a(&autocomp);
	do_autocomp(line, &autocomp);
}
