/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliaas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:45:21 by malaine           #+#    #+#             */
/*   Updated: 2017/03/13 17:37:44 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_box
{
	t_string	right;
	t_string	left;
	bool		check;
}				t_box;

typedef struct s_alias
{
	t_array		data;
}				t_alias;

# define NEW_BOX() (t_box){NEW_STRING, NEW_STRING, 0}

char	*check_if_replace(t_alias *alias, char *str)
{
	void	*ite;

	ite = ARRAY_ITERATOR(&alias->data);
	while(ARRAY_HASNEXT(&alias->data, ite))
	{
		if (ft_strcmp(str, ft_string((t_box *)ite)->left) == 0
			&& ((t_box *)ite)->check == 0)
		{
			((t_box *)ite)->check = 1;
			return (check_if_replace(alias, (char *)ite->right));
		}
	}
	return (str);
}

int		check_if_equal(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == '=')
			return (0);
	return (1);
}

int		add_alias(t_alias *alias, char *str)
{
	split = ft_strchr(str, '=');
	*split = '\0';
	tmp = NEW_BOX();
	STR_JOIN_CS(&tmp.left, str, ft_strlen(str));
	STR_JOIN_CS(&tmp.right, split + 1, ft_strlen(split + 1));
	fta_append(&alias->data, &tmp, 1);
	free(str);
	return (0);
}

void	print_alias_if_exist(t_alias *alias, char *str)
{
	void    *ite;

    ite = ARRAY_GET(&alias->data, -1);
    while(ARRAY_HASNEXT(&alias->data, ite))
        if (ft_strcmp(str, (char *)ite.right) == 0)
		{
			printf("%s=%s\n", str, (char *)((t_box *)ite).left);
			break ;
		}
}

int     bi_alias_init(t_alias *alias)
{
    int         fd;
    int         ret;
    char        *str;
    char        *split;
	t_box		tmp;

	alias->data = NEW_ARRAY(t_box);
    if ((fd = open("/tmp/42sh_alias.txt", O_RDWR | O_CREAT,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        fd = open("/tmp/42sh_alias.txt", O_RDWR);
    while ((ret = get_next_line(fd, &str)) > 0)
		add_alias(str);
    close(fd);
    return (0);
}

int		alias(t_alias *alias, int argc, char ** argv)
{
	int i;

	i = -1;
	bi_alias_init(l, alias);
	while (++i < argc - 1)
	{
		if (check_if_equal(argv[i]) == 0)
			add_alias(alias, argv[i]);
		else
			print_alias_if_exit(alias, argv[i]);
	}
}
