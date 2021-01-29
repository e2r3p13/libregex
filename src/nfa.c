/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nfa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:54:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/01/29 10:45:00 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libregex.h"

static int lnkv_init(t_lnkv *vec)
{
	vec->size = 0;
	vec->capacity = DFL_VEC_CAPACITY;
	if (!(vec->links = malloc(sizeof(t_lnk) * vec->capacity)))
		return (-1);
	return (0);
}

static int lnkv_realloc(t_lnkv *vec)
{
	t_lnk	*new_links;
	size_t	new_cap;

	new_cap = 2 * vec->capacity;
	if (!(new_links = malloc(sizeof(t_lnk) * new_cap)))
		return (-1);
	for (size_t i = 0; i < vec->size; i++)
	{
		new_links[i].c = vec->links[i].c;
		new_links[i].next = vec->links[i].next;
	}
	free(vec->links);
	vec->links = new_links;
	vec->capacity = new_cap;
	return (0);
}

static int lnkv_push(t_lnkv *vec, char c, t_nfa *next)
{
	if (vec->size == vec->capacity && lnkv_realloc(vec) < 0)
		return (-1);
	vec->links[vec->size].c = c;
	vec->links[vec->size].next = next;
	vec->size++;
	return (0);
}

t_nfa *nfa_new_node(bool is_final_state)
{
	t_nfa *node;

	if (!(node = malloc(sizeof(t_nfa))))
		return (NULL);
	if (lnkv_init(&node->links) < 0)
	{
		free(node);
		return (NULL);
	}
	node->is_final_state = is_final_state;
	return (node);
}

int nfa_add_link(t_nfa *node, char c, t_nfa *next)
{
	return (lnkv_push(&node->links, c, next));
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
