/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <tmertz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 03:37:01 by tmertz            #+#    #+#             */
/*   Updated: 2014/03/27 20:25:12 by jburet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error_messages.h"

int		ft_puterror_nofile(char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": No such file or directory.", 2);
	return (-1);
}

int		ft_puterror_nopermission(char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": Permission denied.", 2);
	return (-1);
}

int		ft_puterror_notdir(char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": Not a directory.", 2);
	return (-1);
}

int		ft_puterror_noenv(void)
{
	ft_putendl_fd("Warning : There is no env", 2);
	return (-1);
}
