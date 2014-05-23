/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jburet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:55:18 by jburet            #+#    #+#             */
/*   Updated: 2014/05/23 17:42:58 by tmertz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_tree		*ft_parser(t_list *tokens)
{
	t_tree		*tree;
	t_elem		*elem;

	tree = NULL;
	elem = tokens->first;
	while (elem != NULL)
	{
		ft_putendl(((t_token *)elem->value)->lexen);
		elem =elem->next;
	}
	tree = ft_tree_init(tree);
	if (!ft_grammar(tokens))
		return (NULL);
	tree = ft_parser_make_tree(tree, tokens, NULL, 0);
	ft_print_tree(tree->root, 0);
	return (tree);
}

t_elem		*ft_find_farest_redirection(t_elem *elem)
{
	t_elem		*elem2;

	while (elem != NULL && ((t_token *)elem->value)->type != 2)
		elem = elem->next;
	if (elem != NULL)
	{
		elem2 = elem->next;
		while (elem2 != NULL && ((t_token *)elem2->value)->type != 2)
			elem2 = elem2->next;
		if (elem2 != NULL)
			return (elem2);
	}
	return (elem);
}

t_list		*ft_sh_split_list_l(t_elem *elem, t_list *list)
{
	t_list		*new_list;
	int			j;

	j = 0;
	new_list = NULL;
	new_list = ft_list_init(new_list);
	if (elem->next)
		(elem->next)->previous = NULL;
	new_list->first = list->first;
	new_list->last = elem;
	elem->next = NULL;
	elem = list->first;
	while (elem != NULL)
	{
		j++;
		elem = elem->next;
	}
	new_list->size = j;
	return (new_list);
}
