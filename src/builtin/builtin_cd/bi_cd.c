/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:31:46 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/20 21:02:13 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		check_errors(t_env *env, char *path)
{
	int				status;
	struct stat		dir;

	status = access(path, F_OK);
	if (status != 0)
	{
		NO_FILE_OR_DIR("cd", path);
		return (1);
	}
	status = access(path, X_OK);
	if (status != 0)
	{
		NO_PERMISSION("cd", path);
		return (1);
	}
	if (stat(path, &dir) == 0 && S_ISDIR(dir.st_mode))
		return (0);
	else
		NOT_A_DIR("cd", path);
	return (1);
}

static int		basic_cd(t_env *env, char *path)
{
	char	pwd[PATH_MAX];
	char	tmp[PATH_MAX];
	char	*ptr;
	int		status;

	ft_bzero(pwd, PATH_MAX);
	ft_bzero(tmp, PATH_MAX);
	ptr = getcwd(pwd, PATH_MAX);

	status = chdir(path);
	if (status == 0)
	{
		if (ptr != NULL)
			env_set(env, "OLDPWD", pwd);
		ptr = getcwd(pwd, PATH_MAX);
		if (ptr != NULL)
			env_set(env, "PWD", pwd);
		return (0);
	}
	return (1);
}

int		bi_cd(t_env	*env, char *path)
{
	t_env_cell	*cell;

	cell = NULL;
	if (path != NULL)
	{
		if (!ft_strcmp(path, "-"))
		{
			cell = find_cell(env, "OLDPWD");
			if (cell == NULL && check_errors(env,path) == 1)
				return (1);
			return (basic_cd(env, cell->value));
		}
		else if (!ft_strcmp(path, "~"))
		{
			cell = find_cell(env, "HOME");
			if (cell == NULL && check_errors(env,path) == 1)
				return (1);
			return (basic_cd(env, cell->value));
		}
		else
		{
			if (check_errors(env,path) == 1)
				return (1);
			return (basic_cd(env, path));
		}
	}
	else
		if ((cell = find_cell(env, "HOME")))
			return (basic_cd(env, cell->value));
	return (1);
}
