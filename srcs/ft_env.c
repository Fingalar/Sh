/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 15:19:28 by cmaublan          #+#    #+#             */
/*   Updated: 2014/06/20 16:51:22 by tmertz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_env.h"
#include <dirent.h>
#include <stdlib.h>
#include "../includes/ft_hash.h"
#include "../includes/structs.h"
#include "../includes/history.h"
#include "../includes/config.h"
#include "../includes/singleton.h"

t_sh		*ft_make_sh(t_sh *sh, char **environ)
{
	int		i;

	i = 0;
	sh = get_sh();
	if (!sh || !environ[0])
		return (NULL);
	while (environ[i] != NULL)
		i++;
	sh->env_size = i;
	sh->env = (char **)ft_memalloc(sizeof(char *) * (sh->env_size + 1));
	if (!sh->env)
		return (NULL);
	i = -1;
	while (environ[++i] != NULL)
		sh->env[i] = ft_strdup(environ[i]);
	sh->paths = (t_list **)ft_memalloc(sizeof(t_list *) * SIZE_TABLE + 1);
	sh->history = recup_hist(sh);
	sh->var = ft_list_init(sh->var);
	ft_cpy_pwd(sh);
	ft_set_paths(sh);
	create_file_config(sh);
	ft_set_loc(sh);
	return (sh);
}

char		*ft_get_var(t_sh *sh, char *name)
{
	int		i;

	i = 0;
	while (sh->env[i] != NULL)
	{
		if (ft_strncmp(sh->env[i], name, ft_strlen(name)) == 0)
			return (sh->env[i] + (ft_strlen(name) + 1));
		i++;
	}
	return (NULL);
}

void		ft_set_paths(t_sh *sh)
{
	int				i;
	char			**paths;
	DIR				*c_dir;
	struct dirent	*file;

	i = 0;
	paths = ft_strsplit(ft_get_var(sh, "PATH"), ':');
	while (paths[i] != '\0')
	{
		paths[i] = ft_strjoin(paths[i], "/");
		c_dir = opendir(paths[i]);
		if (!c_dir)
			return ;
		while ((file = readdir(c_dir)) != NULL)
		{
			if (file->d_name[0] != '.')
				ft_hash(sh, ft_strjoin(paths[i], file->d_name), file->d_name);
		}
		free(paths[i]);
		i++;
	}
	free(paths);
}

void		ft_env(t_sh *sh, t_cmd *cmd)
{
	if (cmd)
	{
		if (!cmd->args[1])
			ft_printenv(sh);
	}
}

void		ft_printenv(t_sh *sh)
{
	int		i;

	i = 0;
	while (i < sh->env_size)
	{
		if (sh->env[i] != NULL)
			ft_putendl(sh->env[i]);
		i++;
	}
}
