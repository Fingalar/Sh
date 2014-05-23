/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <tmertz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 04:59:20 by tmertz            #+#    #+#             */
/*   Updated: 2014/05/23 18:59:11 by tmertz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../libft/libft.h"

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_cmd
{
	char			*cmd;
	char			**args;
}					t_cmd;

typedef struct		s_sh
{
	t_list			**paths;
	t_hist			*history;
	char			**env;
	int				env_size;
	int				in;
	int				out;
}					t_sh;

typedef struct		s_word
{
	int				k;
	char			quote;
	char			*result;
	int				status;
}					t_word;

typedef struct		s_token
{
	char			*lexen;
	int				type;
}					t_token;

#endif
