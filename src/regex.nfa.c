/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:54:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/01/29 16:21:43 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libregex.h"

bool nfa_match(t_substr *substring, char c)
{
	return (false);
}

static void	nfa_link_init(t_link *link)
{
	link->match = &nfa_match;
	ft_bzero(link->substr, sizeof(t_substr));
	link->next = NULL;
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

bool dostrmatch(t_nfa *nfa, const char *str)
{
	while (*str)
	{
		char current = *str;
		bool found = false;

		for (size_t i = 0; i < nfa->links.size; i++)
		{
			t_lnk link = nfa->links.links[i];
			if (current == link.c)
			{
				found = true;
				nfa = link.next;
				break ;
			}
		}
		if (!found)
			return (false);
		str++;
	}
	return (nfa->is_final_state);
}
