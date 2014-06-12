/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyguel <nyguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 19:01:23 by nyguel            #+#    #+#             */
/*   Updated: 2014/06/06 19:44:43 by nyguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "term.h"

static char	*ft_add_char(char c, char *line)
{
	int			j;
	char		*line2;

	j = ft_strlen(line);
	line2 = ft_strnew(j + 2);
	ft_strcpy(line2, line);
	free(line);
	line2[j] = c;
	line2[j + 1] = '\0';
	return (line2);
}

static char	ft_read_char2(t_read *opt, int *i)
{
	char	c[1];

	c[0] = 0;
	if (read(opt->u, c, 1) == 1)
	{
		*i = *i + 1;
		if (opt->s == 0)
			ft_putchar(c[0]);
		return (c[0]);
	}
	return (-1);
}

static void	ft_init_var(char **line, t_read *opt, char *c, time_t t[2])
{
	int flags;

	flags = fcntl(opt->u, F_GETFL, 0);
	fcntl(opt->u, F_SETFL, flags | O_NONBLOCK);
	*line = (char *)malloc(sizeof(char));
	*line[0] = '\0';
	*c = '\0';
	t[0] = time(&t[0]);
	t[1] = t[0];
}

int			ft_read_line(t_read *opt, t_sh *sh)
{
	int		i;
	int		max_len;
	char	c;
	char	*line;
	time_t	t[2];

	ft_set_term();
	ft_init_var(&line, opt, &c, t);
	i = 0;
	max_len = (opt->k == -1) ? 99999999 : opt->k;
	while (i < max_len && c != opt->d && (int)t[1] < (int)t[0] + opt->t)
	{
		c = ft_read_char2(opt, &i);
		if (c != -1 && c != opt->d)
			line = ft_add_char(c, line);
		t[1] = time(&t[1]);
	}
	ft_unset_term();
	i = fcntl(opt->u, F_GETFL, 0);
	fcntl(opt->u, F_SETFL, i & ~O_NONBLOCK);
	if (opt->e == 1)
		ft_putendl(line);
	return (0);
	(void)sh;
}
