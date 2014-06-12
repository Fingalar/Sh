/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <tmertz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 02:01:53 by tmertz            #+#    #+#             */
/*   Updated: 2014/05/27 15:45:40 by tmertz           ###   ########.fr       */
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
					return (ft_update_env(sh, cmd->args[1]));
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
		return (ft_special_cd(sh, cmd->args[1]));
}

void	ft_relative_path(t_sh *sh, char *path, int i)
{
	char	**pathes;
	int		j;

	j = -1;
	pathes = ft_strsplit(path, '/');
	while (pathes[++j])
	{
		if (!ft_strcmp(pathes[j], ".."))
			sh->env[i] = ft_strsub_rchr(sh->env[i], '/');
		else
			sh->env[i] = ft_strjoin(ft_strjoin(sh->env[i], "/"), pathes[j]);
	}
	sh->pwd = sh->env[i];
}

int		ft_update_env(t_sh *sh, char *path)
{
	int		i;
	int		k;

	i = ft_getenv_id(sh->env, "PWD", 3);
	k = ft_getenv_id(sh->env, "OLDPWD", 6);
	if (sh->env[k] == NULL)
	{
		sh->env[k] = ft_strdup(sh->oldpwd);
		sh->env[k + 1] = 0;
	}
	i = (i == k) ? i + 1 : i;
	if (sh->env[i] == NULL)
	{
		sh->env[i] = ft_strdup(sh->pwd);
		sh->env[i + 1] = 0;
	}
	sh->env[k] = ft_strjoin("OLDPWD=", sh->env[i] + 4);
	sh->oldpwd = sh->env[k];
	if (!ft_strcmp(sh->env[i] + 4, "/"))
		return (0);
	if (path[0] == '/')
	{
		sh->env[i] = ft_strjoin("PWD=", path);
		sh->pwd = sh->env[i];
	}
	else
		ft_relative_path(sh, path, i);
	return (0);
}

int		ft_special_cd(t_sh *sh, char *spec)
{
	int		i;
	int		j;

	i = ft_getenv_id(sh->env, "HOME", 4);
	j = ft_getenv_id(sh->env, "OLDPWD", 6);
	if (sh->env[j] == NULL)
	{
		sh->env[j] = ft_strdup(sh->oldpwd);
		sh->env[j + 1] = 0;
	}
	i = (i == j) ? i + 1 : i;
	if (sh->env[i] == NULL)
	{
		sh->env[i] = ft_strdup(sh->home);
		sh->env[i + 1] = 0;
	}
	ft_putchar('a');
	if (spec == NULL || !ft_strcmp(spec, "~"))
	{
		chdir(sh->env[i] + 5);
		ft_update_env(sh, sh->env[i] + 5);
	}
	else
	{
		chdir(sh->env[j] + 7);
		ft_update_env(sh, sh->env[j] + 7);
	}
	return (0);
}

int		ft_getenv_id(char **environ, char *str, int size)
{
	int		i;

	i = 0;
	while (environ[i] && (ft_strncmp(environ[i], str, size)))
		i++;
	return (i);
}
