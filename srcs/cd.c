/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <tmertz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 02:01:53 by tmertz            #+#    #+#             */
/*   Updated: 2014/04/27 15:53:59 by tmertz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cd.h"

int		ft_change_directory(t_sh *sh, t_cmd *cmd)
{
	struct stat		stats;

	if (cmd->args[1] != NULL && ft_strcmp(cmd->args[1], "~")
			&& ft_strcmp(cmd->args[1], "-"))
	{
		if (stat(cmd->args[1], &stats) != -1)
		{
			if (stats.st_mode & S_IFDIR)
			{
				if (stats.st_mode & S_IRUSR)
				{
					chdir(cmd->args[1]);
					return (ft_update_env(sh->env, cmd->args[1]));
				}
				else
					return (ft_puterror_nopermission(cmd->args[1]));
			}
			else
				return (ft_puterror_notdir(cmd->args[1]));
		}
		else
			return (ft_puterror_nofile(cmd->args[1]));
	}
	else
		return (ft_special_cd(sh->env, cmd->args[1]));
}

void	ft_relative_path(char **environ, char *path, int i)
{
	char	**pathes;
	int		j;

	j = -1;
	pathes = ft_strsplit(path, '/');
	while (pathes[++j])
	{
		if (!ft_strcmp(pathes[j], ".."))
			environ[i] = ft_strsub_rchr(environ[i], '/');
		else
			environ[i] = ft_strjoin(ft_strjoin(environ[i], "/"), pathes[j]);
	}
}

int		ft_update_env(char **environ, char *path)
{
	int		i;
	int		k;

	i = ft_getenv_id(environ, "PWD", 3);
	k = ft_getenv_id(environ, "OLDPWD", 6);
	environ[k] = ft_strjoin("OLDPWD=", environ[i] + 4);
	if (!ft_strcmp(environ[i] + 4, "/"))
		return (0);
	if (path[0] == '/')
		environ[i] = ft_strjoin("PWD=", path);
	else
		ft_relative_path(environ, path, i);
	return (0);
}

int		ft_special_cd(char **environ, char *spec)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((ft_strncmp(environ[i], "HOME", 4)))
		i++;
	while ((ft_strncmp(environ[j], "OLDPWD", 6)))
		j++;
	if (spec == NULL || !ft_strcmp(spec, "~"))
	{
		chdir(environ[i] + 5);
		ft_update_env(environ, environ[i] + 5);
	}
	else
	{
		chdir(environ[j] + 7);
		ft_update_env(environ, environ[j] + 7);
	}
	return (0);
}

int		ft_getenv_id(char **environ, char *str, int size)
{
	int		i;

	i = 0;
	while ((ft_strncmp(environ[i], str, size)))
		i++;
	return (i);
}
