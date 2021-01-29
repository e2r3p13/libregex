/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:54:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/01/29 17:30:33 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libregex.h"

bool nfa_match(t_substr *s, char c)
{
	if (!s)
		return (true);
	if (s->start == s->end && *(s->start) == c)
		return (true);
}

t_nfa *nfa_new_node(bool is_final_state)
{
	t_nfa *node;

	if (!(node = malloc(sizeof(t_nfa))))
		return (NULL);
	node->is_final_state = is_final_state;
	nfa_link_init(node->left);
	nfa_link_init(node->right);

	return (node);
}

static void	nfa_link_init(t_link *link)
{
	link->match = &nfa_match;
	ft_bzero(link->substr, sizeof(t_substr));
	link->next = NULL;
}

void nfa_add_link(t_nfa *node, t_substr substr, t_nfa *next)
{
	if (!node->left.next)
	{
		node->left.next = next;
		node->left.substr = substr;
	}
	else
	{
		node->right.next = next;
		node->right.substr = substr;
	}
}

bool nfa_dostrmatch(t_nfa *nfa, const char *str)
{
	while (*str)
	{
		if (nfa->left.match(nfa->left.substr, *str))
			nfa = nfa->left;
		else if (nfa->right.match(nfa->right.substr, *str))
			nfa = nfa->right;
		else
			return (false);
		str++;
	}
	return (nfa->is_final_state);
}
