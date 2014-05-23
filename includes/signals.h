/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <tmertz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 22:16:18 by tmertz            #+#    #+#             */
/*   Updated: 2014/03/27 18:59:23 by jburet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "term.h"
# include "../libft/libft.h"

void	handle_segfault(void);
void	ft_handle_signals(int signum);
void	catch_signals(void);

#endif
