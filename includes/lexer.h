/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmertz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 16:23:06 by tmertz            #+#    #+#             */
/*   Updated: 2014/03/27 20:09:07 by jburet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <stdlib.h>
# include "structs.h"
# include "wildcard.h"

t_list		*ft_lexer(char *line);
int			ft_create_token(t_list *tokens, char *lex, int type);
t_token		*ft_init_token(char *lex, int type);
int			ft_add_word_size(char *line, int i);
int			ft_add_word(t_list *tokens, char *line, int i);
char		ft_handle_backslash(char *line, int i, int status);
char		ft_add_special_carac(char *lone, int i, char c);
int			ft_add_subshell(t_list *tokens, char *line, int i);
int			ft_check_redirection(t_list *tokens, char *line, int i);
int			ft_check_operator(t_list *tokens, char *line, int i);

#endif
