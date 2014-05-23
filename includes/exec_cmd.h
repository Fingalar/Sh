/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <tmertz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 14:26:53 by tmertz            #+#    #+#             */
/*   Updated: 2014/03/27 05:04:45 by tmertz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H
# include "structs.h"
# include "echo.h"
# include "parser.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "ft_hash.h"
# include "builtins.h"
# include "cd.h"

int		ft_check_cmd(t_node *node, t_sh *sh);
int		ft_exec_cmd(t_cmd *cmd, char *path, t_sh *sh);

#endif
