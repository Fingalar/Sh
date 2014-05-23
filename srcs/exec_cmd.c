/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <tmertz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 16:10:00 by tmertz            #+#    #+#             */
/*   Updated: 2014/05/23 18:24:11 by tmertz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_cmd.h"
#include "../includes/ft_env.h"
#include "../includes/config.h"

int		ft_check_if_builltin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (2);
	if (!ft_strcmp(cmd, "env"))
		return (3);
	if (!ft_strcmp(cmd, "setenv"))
		return (4);
	if (!ft_strcmp(cmd, "unsetenv"))
		return (5);
	if (!ft_strcmp(cmd, "echo"))
		return (6);
	return (0);
}

int		ft_exec_builltin(t_cmd *cmd, t_sh *sh, int nbr)
{
	if (nbr == 6)
		return (ft_echo(cmd));
	if (nbr == 2)
		return (ft_exit(cmd));
	if (nbr == 1)
		return (ft_change_directory(sh, cmd));
	if (nbr == 5)
		return (ft_unsetenv(sh, cmd));
	if (nbr == 4)
		return (ft_setenv(sh, cmd));
	if (nbr == 3)
		ft_env(sh, cmd);
	return (0);
}

char	*get_cmd(t_sh *sh, t_cmd *cmd)
{
	int		i;
	char	**pathes;

	i = -1;
	while (sh->env[++i] != NULL)
	{
		if (!ft_strncmp("PATH=", sh->env[i], 5))
			pathes = ft_strsplit(sh->env[i], ':');
	}
	i = -1;
	while (pathes[++i] != NULL)
	{
		if (access(ft_strjoin(ft_strjoin(pathes[i], "/"), cmd->cmd), X_OK) == 0)
			return (ft_strjoin(ft_strjoin(pathes[i], "/"), cmd->cmd));
	}
	return (NULL);
}

int		ft_check_cmd(t_node *node, t_sh *sh)
{
	char	*path;
	t_cmd	*cmd;
	int		nbr;

	path = NULL;
	cmd = (t_cmd *)node->value;
	cmd->cmd = alias(sh, cmd->cmd);
	if ((nbr = ft_check_if_builltin(cmd->cmd)) != 0)
		return (ft_exec_builltin(cmd, sh, nbr));
	if (ft_strchr(cmd->cmd, '/') != NULL)
	{
		if (access(cmd->cmd, X_OK) == 0)
			return (ft_exec_cmd(cmd, cmd->cmd, sh));
		else
			return (0);
	}
	else if ((path = get_cmd(sh, cmd)) == NULL)
		return (ft_cmd_not_found(cmd->cmd));
	else
	{
		if (access(path, X_OK) == 0)
			return (ft_exec_cmd(cmd, path, sh));
		else
			return (0);
	}
}

int		ft_exec_cmd(t_cmd *cmd, char *path, t_sh *sh)
{
	pid_t	process;
	int		ret;

	ret = 0;
	process = fork();
	if (process == 0)
	{
		execve(path, cmd->args, sh->env);
		exit(1);
	}
	else
		waitpid(process, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}
