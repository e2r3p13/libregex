/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:29:49 by bccyv             #+#    #+#             */
/*   Updated: 2021/01/30 15:26:49 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"

static bool match_link(t_substr *s, char c)
{
	if (!s)
		return (true); // Epsilon link

	if (s->start == s->end)
		return (*(s->start) == c); // Single char pattern

	return (false); // More complex patterns need to be implemented
}

static void	link_init(t_link *ln)
{
	ln->match = &match_link;
	ft_bzero(ln->substr, sizeof(t_substr));
	ln->next = NULL;
}

t_state *state_new(bool is_final)
{
	t_state *st;

	if (!(st = malloc(sizeof(t_state))))
		return (NULL);

	st->is_final = is_final;

	link_init(st->left);
	link_init(st->right);

	return (node);
}

void state_add_link(t_state *st, t_pattern pattern, t_state *next)
{
	if (!st->left.next)
	{
		st->left.next = next;
		st->left.substr = pattern;
	}
	else
	{
		st->right.next = next;
		st->right.substr = pattern;
	}
}
